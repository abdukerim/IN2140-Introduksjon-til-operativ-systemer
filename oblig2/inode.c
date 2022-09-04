#include "allocation.h"
#include "inode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BLOCKSIZE 4096


static int current_id = 0;

struct inode* create_file( struct inode* parent, char* name, char readonly, int size_in_bytes )
{
  if(!parent) {
    return NULL;
  }
  else if(!(parent->is_directory) || find_inode_by_name(parent,name)) return NULL;

  struct inode* new_file =  (struct inode*)malloc(sizeof(struct inode));

  if (!new_file) {
		fprintf(stderr, "Malloc failed!.\n");
		exit(EXIT_FAILURE);
	}

  new_file->id = current_id++;
  new_file->name = strdup(name);
  new_file->is_directory = 0;
  new_file->is_readonly = readonly;
  new_file->filesize = size_in_bytes;

  int block_nums = size_in_bytes / BLOCKSIZE;

  if(!(size_in_bytes%BLOCKSIZE)) block_nums++;

  size_t* entries = malloc(sizeof(size_t)* block_nums);

  for (int i = 0; i < block_nums; i++) {
    entries[i] = allocate_block();
  }

  new_file->num_entries = block_nums;
  new_file->entries = entries;

  size_t* new_entries = (size_t*) malloc(sizeof(size_t)*(parent->num_entries+1));

	if (!(parent->num_entries)) {
		parent->entries = new_entries;
	}
	else {
		memcpy(new_entries,parent->entries,parent->num_entries*sizeof(size_t));
		free(parent->entries);
		parent->entries = new_entries;
	}
	parent->entries[parent->num_entries] = new_file;

	parent->num_entries++;

  return new_file;
}

struct inode* create_dir( struct inode* parent, char* name )
{
  if(!parent) {
    struct inode* new_dir = malloc(sizeof(struct inode));
    if(!new_dir) {
      fprintf(stderr, "Malloc Failed.\n");
      exit(EXIT_FAILURE);
    }
    new_dir->id = current_id++;
    new_dir->name = strdup(name);
    if(!new_dir->name) {
      fprintf(stderr, "strdup failed.\n");
      exit(EXIT_FAILURE);
    }
    new_dir->is_directory = 1;
    new_dir->is_readonly = 0;
    new_dir->filesize = 0;
    new_dir->num_entries = 0;
    new_dir->entries = NULL;
    return new_dir;
  }
  else {
    if(!(parent->is_directory)) return NULL;

    if(find_inode_by_name(parent,name)) return NULL;

    struct inode* new_dir = (struct inode*) malloc(sizeof(struct inode));

    if(!new_dir) {
      fprintf(stderr, "Malloc Failed.\n");
      exit(EXIT_FAILURE);
    }
    new_dir->id = current_id++;
    new_dir->name = strdup(name);
    new_dir->is_directory = 1;
    new_dir->is_readonly = 0;
    new_dir->filesize = 0;
    new_dir->num_entries = 0;
    new_dir->entries = NULL;

    size_t* new_entries = (size_t*)malloc(sizeof(size_t)*parent->num_entries);

    if(!(parent->num_entries)){
      parent->entries = new_entries;
    }
    else {
      memcpy(new_entries,parent->entries,parent->num_entries*sizeof(size_t));
      free(parent->entries);
      parent->entries = new_entries;
    }
    parent->entries[parent->num_entries] = new_dir;

		parent->num_entries++;

    return new_dir;
  }
}

struct inode* find_inode_by_name( struct inode* parent, char* name )
{
  for (int i = 0; i < parent->entries; i++) {
    if(strcmp(((struct inode*)parent->entries[i])->name, name)) {

      return (struct inode*)(parent->entries[i]);
    }
  }
  return NULL;
}

struct inode *read_inodes(FILE *file) {
	int id;

	int ret = fread(&id, 4, 1, file);
	if (ret == 0) {
		printf("End of file.\n");
		return NULL;
	}

	int name_len;

	if (!(fread(&name_len,4,1,file))) exit(EXIT_FAILURE);

	char* name = (char*) malloc(sizeof(char)*name_len);
	if (!name) {
		fprintf(stderr, "Malloc failed.\n");
		exit(EXIT_FAILURE);
	}

	if(!(fread(name,name_len*sizeof(char),1,file))) exit(EXIT_FAILURE);

	char is_directory;
	if(!(fread(&is_directory,1,1,file))) exit(EXIT_FAILURE);

	char is_readonly;
	if (!(fread(&is_readonly,1,1,file))) exit(EXIT_FAILURE);

	int filesize;
	if (!(fread(&filesize,4,1,file))) exit(EXIT_FAILURE);

	int num_entries;
	if (!(fread(&num_entries,4,1,file))) exit(EXIT_FAILURE);

	size_t* entries = (size_t*) malloc(sizeof(size_t)*num_entries);
	if (!entries) {
		fprintf(stderr, "Malloc failed.\n");
		exit(EXIT_FAILURE);
	}

	struct inode* inode = malloc(sizeof(struct inode));
	if (!inode) {
		fprintf(stderr, "Malloc failed.\n");
		exit(EXIT_FAILURE);
	}

	if (is_directory) {
		fseek(file,sizeof(size_t)*num_entries,SEEK_CUR);

		for (int i = 0; i < num_entries; i++) {
			entries[i] = read_inodes(file);
		}
	}

	else {
		for (int i = 0; i < num_entries; i++) {
			size_t entry;
			fread(&entry,sizeof(size_t),1,file);
			entries[i] = entry;
		}

	}

	inode->id = id;
	inode->name = name;
	inode->is_directory = is_directory;
	inode->is_readonly = is_readonly;
	inode->filesize = filesize;
	inode->num_entries = num_entries;
	inode->entries = entries;

	return inode;
}

struct inode* load_inodes()
{
	FILE* file = fopen("superblock", "r");

	struct inode* inodes = read_inodes(file);
	fclose(file);
	return inodes;
}

void fs_shutdown( struct inode* inode )
{
  //check if directory
  if(!inode) {
    exit(EXIT_SUCCESS);
  }
  if(!(inode->is_directory)) {
    free(inode->entries);
    free(inode->name);
    free(inode);
    exit(EXIT_SUCCESS);
  }
  else {
    for(int i = 0;i < inode->entries;i++) {
      fs_shutdown((struct inode*) inode->entries[i]);
    }
    free(inode->entries);
    free(inode->name);
    free(inode);
  }

}

/* This static variable is used to change the indentation while debug_fs
 * is walking through the tree of inodes and prints information.
 */
static int indent = 0;

void debug_fs( struct inode* node )
{
    if( node == NULL ) return;
    for( int i=0; i<indent; i++ )
        printf("  ");
    if( node->is_directory )
    {
        printf("%s (id %d)\n", node->name, node->id );
        indent++;
        for( int i=0; i<node->num_entries; i++ )
        {
            struct inode* child = (struct inode*)node->entries[i];
            debug_fs( child );
        }
        indent--;
    }
    else
    {
        printf("%s (id %d size %db blocks ", node->name, node->id, node->filesize );
        for( int i=0; i<node->num_entries; i++ )
        {
            printf("%d ", (int)node->entries[i]);
        }
        printf(")\n");
    }
}
