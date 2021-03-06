#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fgetname.h"
#include "namelist.h"

int compare (const void* a, const void* b);

int main(int argc, char **argv){
  char name[NAMELEN];
  int i,j,k,FLAG;
  char* keywords[] = {"auto","double","int","long","break","else","long","switch","case","enum","register","typedef","char","extern","return","union","const","float","short","unsigned","continue","for","signed","void","default","goto","sizeof","volatile","do","if","static","while"};
  if (argc == 1) {
    printf("please provide files to analyze\n");
    return 0;
  }
  namelist nl = make_namelist();
  for(i=1;i<argc;i++){
    FILE *file = fopen(argv[i],"r");
    while(fgetname(name, sizeof(name), file)){
      FLAG = 0;
      for(j=0;j<32;j++){
	if(0==(strcmp(keywords[j],name))){
	  FLAG=1;
	}
      }
      if(FLAG==0){
	add_name(nl, name);
      }
    }
    fclose(file);
  }
  
  qsort(nl->names,nl->size,sizeof(struct namestat),compare);
  
  for(k=0;k<nl->size;k++){
    printf("%s %d\n",nl->names[k].name,nl->names[k].count);
  }
  
  return 0;
}


int compare(const void *p1, const void *p2)
       {
          return strcmp(((struct namestat *)p1)->name, ((struct namestat*)p2)->name);
       }


