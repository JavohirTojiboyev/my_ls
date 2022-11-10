#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#define LISTNODE typedef struct p_listnode{\
    char *nomi;\
    struct stat f_stat;\
    struct p_listnode* next;\
}\
listnode;

#define ROYXAT void royxat_ch(listnode* files, char bayroq){\
    while(files){\
        if(bayroq == 't' || !bayroq){\
            if(files->nomi[0] != '.')\
            printf("%s\n", files->nomi);\
        }else{\
            printf("%s\n", files->nomi);\
        }\
        files = files->next;\
    }\
}

#define LCH listnode* check(){\
    listnode* tugun1 = (listnode*)malloc(sizeof(listnode));\
    listnode* tugun2 = (listnode*)malloc(sizeof(listnode));\
    listnode* tugun3 = (listnode*)malloc(sizeof(listnode));\
    tugun2->nomi = "/"; tugun2->next = NULL;\
    tugun3->nomi = "/tmp/"; tugun3->next = NULL;\
    tugun1->nomi = ".";\
    tugun1->next = tugun2;\
    tugun2->next = tugun3;\
    return tugun1;\
}

#define S_CMP int s_cmp(char *p1, char *p2){\
    int k = 0;\
    while((p1[k]==p2[k]) && (p1[k] != '\0') && (p2[k] != '\0')){\
        k++;\
    }\
    return p1[k] - p2[k];\
}

#define OQ listnode* orqasidan_qosh(listnode *boshi, char * p_name, struct stat file_stat){\
    listnode *yangi_node = malloc(sizeof(listnode));\
    yangi_node->nomi = p_name;\
    yangi_node->next = NULL;\
    yangi_node->f_stat = file_stat;\
    if(boshi == NULL)\
        boshi = yangi_node;\
    else\
    {\
        listnode *l_node = boshi;\
        while (l_node->next != NULL) {\
            l_node = l_node->next;\
        }\
        l_node->next = yangi_node;\
    }\
    return boshi;\
}


#define LIST listnode* sortlash(listnode* tugun, struct stat filestat, char bayroq){\
    listnode* boshi = tugun;\
    while(boshi->next != NULL){\
        listnode* b = boshi->next;\
        while(b != NULL){\
            if(bayroq == 't'|| bayroq == 'x'){\
                if(boshi->f_stat.st_mtim.tv_sec == b->f_stat.st_mtim.tv_sec){\
                    if(boshi->f_stat.st_mtim.tv_nsec <= b->f_stat.st_mtim.tv_nsec){\
                        char* swop = (char*)malloc(25);\
                        swop = boshi->nomi;\
                        boshi->nomi = b->nomi;\
                        b->nomi = swop;\
                        filestat = boshi->f_stat;\
                        boshi->f_stat = b->f_stat;\
                        b->f_stat = filestat;\
                    }\
                }else if(boshi->f_stat.st_mtim.tv_sec <= b->f_stat.st_mtim.tv_sec ){\
                    char* swop = (char*)malloc(33);\
                    swop = boshi->nomi;\
                    boshi->nomi =b->nomi;\
                    b->nomi = swop;\
                    filestat = boshi->f_stat;\
                    boshi->f_stat = b->f_stat;\
                    b->f_stat = filestat;\
                }\
            }else{\
                if(s_cmp(boshi->nomi, b->nomi)>= 0){\
                    char* swop = (char*)malloc(33);\
                    swop = boshi->nomi;\
                    boshi->nomi =b->nomi;\
                    b->nomi = swop;\
                }\
            }\
            b = b->next;\
        }\
        boshi = boshi->next;\
    }\
    return tugun;\
}


#define MY_P int my_p(char bayroq){\
    DIR *papka;\
    struct dirent *kirish;\
    struct stat file__stat;\
    listnode *nod = (listnode*)malloc(sizeof(listnode));\
    nod=NULL;\
    papka = opendir(".");\
    if(papka == NULL)\
        perror("cannot read the directory");\
    while((kirish= readdir(papka))){\
        stat(kirish->d_name, &file__stat);\
        nod =orqasidan_qosh(nod, kirish->d_name, file__stat);\
    }\
    nod = sortlash(nod, file__stat, bayroq);\
    royxat_ch(nod, bayroq);\
    closedir(papka);\
    return 0;\
}

#define BRNMA void brnma(listnode* brnma, char bayroq){\
    struct stat ffft;\
    listnode* fl_node = (listnode*)malloc(sizeof(listnode));\
    fl_node = NULL;\
    listnode* pap_node = (listnode*)malloc(sizeof(listnode));\
    pap_node = NULL;\
    int q, fileSoni = 0, dirSoni = 0;\
    while(brnma){\
        q = open(brnma->nomi, O_RDONLY);\
        if(q >= 0){\
            stat(brnma->nomi,&ffft);\
            if(!S_ISDIR(ffft.st_mode)){\
                fl_node =orqasidan_qosh(fl_node, brnma->nomi, ffft);\
                fileSoni++;\
            }else{\
                pap_node =orqasidan_qosh(pap_node, brnma->nomi, ffft);\
                if(s_cmp(brnma->nomi, "/")==0){\
                    pap_node = check();\
                }\
                dirSoni++;\
            }\
        }else{\
           printf("ls: cannot access '%s': No such file or directory\n", brnma->nomi);\
        }\
        brnma = brnma->next;\
    }\
    if(fileSoni > 0){\
        fl_node =sortlash(fl_node, ffft, bayroq);\
        while(fl_node){\
            printf("%s\n", fl_node->nomi);\
            fl_node = fl_node->next;\
        }\
    }\
    if(dirSoni > 0){\
        DIR* papka;\
        struct dirent *kirish;\
        struct stat ffft;\
        while(pap_node){\
            listnode* l_node = (listnode*)malloc(sizeof(listnode));\
            l_node = NULL;\
            papka = opendir(pap_node->nomi);\
            while((kirish = readdir(papka))){\
                stat(kirish->d_name, &ffft);\
                l_node =orqasidan_qosh(l_node, kirish->d_name, ffft);\
            }\
            l_node = sortlash(l_node, ffft, bayroq);\
            if(dirSoni > 1){\
                printf("%s:\n",pap_node->nomi);\
            }\
            royxat_ch(l_node, bayroq);\
            if(pap_node->next != NULL){\
                putchar('\n');\
            }\
            pap_node = pap_node->next;\
        }\
    }\
}

#define INT int main(int ac, char** av){\
    char bayroq;\
    struct stat filest;\
    listnode *l_else = malloc(sizeof(listnode));\
    l_else = NULL;\
    int u  = 0, a = 0, t = 0;\
    for(int i = 1; i < ac; i++){\
        if(s_cmp(av[i], "-a")== 0){\
            bayroq = 'a';\
            a++;\
        }\
        else if(s_cmp(av[i] , "-t")== 0){\
            bayroq = 't';\
            t++;\
        }\
        else if(s_cmp(av[i], "-at")==0 || s_cmp(av[i], "-ta")==0){\
            bayroq = 'x';\
        }\
        else{\
            u++;\
            stat(av[i], &filest);\
            l_else =orqasidan_qosh(l_else, av[i], filest);\
        }\
    }\
    if(t && a) bayroq = 'x';\
    else if(t) bayroq = 't';\
    else if(a) bayroq = 'a';\
    if(u == 0){\
        my_p(bayroq);\
    }else{\
        brnma(l_else, bayroq);\
    }\
}


LISTNODE

ROYXAT

LCH

S_CMP

OQ

LIST

MY_P

BRNMA

INT
