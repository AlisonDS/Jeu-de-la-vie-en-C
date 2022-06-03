#include <stdio.h>
#include <stdlib.h>

const int TAILLE_MATRICE = 15;

int **GRILLE;
int **tmp;


int **creation_matrice(int **matrice);
void placement_cellules_vivantes(int **matrice);
void affichage_matrice(int **matrice);
int voisinage(int **matrice, int coord_x, int coord_y);
void prochaine_generation(int **matrice1, int **matrice2);
//void affichage_nb_voisins(int **matrice);



int **creation_matrice(int **matrice) //Cree une matrice carree et l'alloue dynamiquement
{
    int i, j;

    //allocation de la grille
    matrice = (int**)malloc(sizeof(int*)*TAILLE_MATRICE);
    for (i=0; i<TAILLE_MATRICE; i++) matrice[i] = (int*)calloc(sizeof(int),TAILLE_MATRICE);
    
    return matrice;
}

void placement_cellules_vivantes(int **matrice) //Place des cellules vivantes de facon aleatoire
{
    int x, y, i, j;
    for (i=0; i<TAILLE_MATRICE; i++) for (j=0; j<TAILLE_MATRICE; j++) matrice[i][j] = rand()%2;
}

void affichage_matrice(int **matrice) //Affiche une matrice carree dont la taille est TAILLE_MATRICE
{
    int i, j;

    for (i=0; i<TAILLE_MATRICE; i++)
    {
        for (j=0; j<TAILLE_MATRICE; j++)
        {
            printf("%3d", matrice[i][j]);
        }
    printf("\n");
    }
}

int voisinage(int **matrice, int coord_x, int coord_y) //Compte le nombre de cellules voisines en fonction des coordonnees x et y
{
    int nb_voisins;
    nb_voisins = matrice[(coord_x-1+TAILLE_MATRICE)%TAILLE_MATRICE][(coord_y-1+TAILLE_MATRICE)%TAILLE_MATRICE] 
               + matrice[(coord_x+TAILLE_MATRICE)%TAILLE_MATRICE][(coord_y-1+TAILLE_MATRICE)%TAILLE_MATRICE]
               + matrice[(coord_x+1+TAILLE_MATRICE)%TAILLE_MATRICE][(coord_y-1+TAILLE_MATRICE)%TAILLE_MATRICE] 
               + matrice[(coord_x-1+TAILLE_MATRICE)%TAILLE_MATRICE][(coord_y+TAILLE_MATRICE)%TAILLE_MATRICE] 
               + matrice[(coord_x+1+TAILLE_MATRICE)%TAILLE_MATRICE][(coord_y+TAILLE_MATRICE)%TAILLE_MATRICE] 
               + matrice[(coord_x-1+TAILLE_MATRICE)%TAILLE_MATRICE][(coord_y+1+TAILLE_MATRICE)%TAILLE_MATRICE] 
               + matrice[(coord_x+TAILLE_MATRICE)%TAILLE_MATRICE][(coord_y+1+TAILLE_MATRICE)%TAILLE_MATRICE] 
               + matrice[(coord_x+1+TAILLE_MATRICE)%TAILLE_MATRICE][(coord_y+1+TAILLE_MATRICE)%TAILLE_MATRICE];
    return nb_voisins;
}

void prochaine_generation(int **matrice1, int **matrice2) //Modifie une matrice (matrice1) en fonction du nombre de voisins qu'une cellule possede et affiche une nouvelle generation (matrice2)
{
    int nb_voisins;
    int i, j;
    
    for (i=0; i<TAILLE_MATRICE; i++)
    {
        for (j=0; j<TAILLE_MATRICE; j++)
        {
            nb_voisins = voisinage(matrice1, i, j);                //Compte le nombre de voisins pour la matrice[i][j]

            if (nb_voisins == 3) matrice2[i][j] = 1;               //Si la cellule possede 3 cellules voisines, elle revit
            if (nb_voisins<2 || nb_voisins>3) matrice2[i][j] = 0;  //Si la cellule possede moins de 2 ou plus de 3 voisins, elle meurt
            if (nb_voisins==2) matrice2[i][j] = matrice1[i][j];    //Si la cellule possede 2 cellules voisines, elle reste dans son etat actuel
        }
    }
}

/*
void affichage_nb_voisins(int **matrice) //Affiche le nombre de voisins qu'une cellule possede dans une matrice carree
{
    int i, j, nb_voisins;

    for (i=0; i<TAILLE_MATRICE; i++)
    {
        for (j=0; j<TAILLE_MATRICE; j++)
        {
            nb_voisins = voisinage(matrice, i, j);
            //matrice[i][j] = nb_voisins;
            printf("%3d", nb_voisins);
        }
    printf("\n");
    }
}
*/

int main()
{
    printf("*****************************\n");
    printf("*       JEU DE LA VIE       *\n");
    printf("*                           *\n");
    printf("*     Alison DOS SANTOS     *\n");
    printf("*        Maxim FARAJ        *\n");
    printf("*****************************\n\n");

    //Regles du jeu de la vie 
    printf("Bienvenue dans le jeu de la vie, voici les regles du jeu :\n");
    printf("Une cellule renait, si elle possede trois cellules voisines vivantes.\n");
    printf("Une cellule reste dans son etat actuel, si elle possede deux cellules voisines vivantes.\n");
    printf("Enfin, une cellule meurt, si elle possede moins de deux ou plus de trois cellules voisines.\n\n");
int **tmp_2;
    GRILLE = creation_matrice(GRILLE); //Cree la matrice GRILLE et l'alloue dynamiquement
    tmp = creation_matrice(tmp);       //Cree la matrice tmp et l'alloue dynamiquement

    placement_cellules_vivantes(GRILLE); //Place des cellules vivantes dans la matrice GRILLE de facon aleatoire
    printf("Voici la premiere generation :\n\n");
    affichage_matrice(GRILLE); //Affiche la premiere generation de la matrice GRILLE

    //printf("\n");
    //affichage_nb_voisins(GRILLE);
    //printf("\n");

    while(1)
    {
        prochaine_generation(GRILLE, tmp); //Cree la nouvelle generation de la matrice GRILLE
        printf("\nVoici la generation suivante :\n\n");
        affichage_matrice(tmp); //Affiche la prochaine generation de la matrice GRILLE
        tmp_2=tmp;
        tmp=GRILLE;
        GRILLE=tmp_2;
    }

    return 0;
}