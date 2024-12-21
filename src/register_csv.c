#include <stdio.h>
#include "register_csv.h"

void save_to_csv(const char *filename, float *array, size_t n_cols) {
    FILE *file = fopen(filename, "w"); // ouvrir le fichier en mode écriture ("w")
    
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    
    // Écrire les données dans le fichier CSV
    for (size_t i = 0; i < n_cols; i++) {
            fprintf(file, "%.2f", array[i]); // écrire l'élément
            if (i < n_cols - 1)
                fprintf(file, ","); // Ajouter une virgule entre les éléments
        }
    printf("\ncsv crée\n");
    fclose(file); // fermer le fichier
}