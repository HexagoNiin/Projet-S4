#include "../headers/utils_virtual_disk.h"

int init_disk_raid5(const char* nom_rep, virtual_disk_t* r5Disk) {
    /// \brief Initialise la variable globale virtual_disk_t r5Disk à partir de nom_rep
    /// \param[in] nom_rep : Nom du répertoire contenant les disques virtuels formatés
    /// \return Un entier indiquant si l'opération s'est bien passée
    DIR *rep = opendir(nom_rep);
    struct dirent *disque;
    r5Disk->raidmode = CINQ;
    r5Disk->number_of_files = 0; //Quelle est la différence entre cet attribut et l'attribut ndisk ? En attendant je le mets à 0.
    //Non initialisés : inodes (Il est demandé de ne pas le faire pour l'instant), super_block (Je sais pas encore ce que c'est sensé être),

    if(rep == NULL) {
        fprintf(stderr, "Une erreur est survenue lors de l'accès au répertoire %s.\n", nom_rep);
        return 1;
    }

    r5Disk->ndisk = 0;
    r5Disk->storage = malloc(sizeof(FILE*));
    while((disque = readdir(rep)) != NULL) {
        struct stat sDisque;
        if(stat(disque->d_name, &sDisque) == -1) {
            fprintf(stderr, "Une erreur est survenue lors de la lecture du disque %s.\n", disque->d_name);
            return 2;
        }
        if(S_ISREG(sDisque.st_mode)) {
            fprintf(stderr, "L'élément %s est étranger au système. L'élément devrait être supprimé ou le système reformaté.\n", disque->d_name);
            return 3;
        }
        r5Disk->ndisk++; //J'imagine que c'est le nombre de disque ? Ce n'est ni commenté, ni documenté.
        r5Disk->storage = realloc(r5Disk->storage, r5Disk->ndisk * sizeof(FILE*));
        r5Disk->storage[r5Disk->ndisk-1] = fopen(disque->d_name, "r");
    }
    return 0;
}

int main() {
    return 0;
}
