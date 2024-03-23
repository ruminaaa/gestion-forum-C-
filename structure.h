#include<stdio.h>
#include<time.h>

struct tm date;

typedef struct profil{
     int num_inscription;
    char nom[50];
    char prenom[50];
    char adresse[50];
    struct tm date_de_naissance;
    char courriel[50];
    long int numero_telephone;

}Profil;



typedef struct auteur{
    char pseudo[50];
    struct tm date_premier_msg;
    struct tm date_dernier_msg;
    int nombre_msg;
    Profil profil;
}Auteur;
typedef struct forum{
    char adresse_internet[50];
    char courriel[50];
    int nbre_rub;

}Forum;
typedef struct rubrique{
    char theme[50];
    struct tm date_de_creation;
    char courriel[50];
    struct Cellule_lien_rub* liste_lien;

}Rubrique;

typedef struct message{
     char titre[50];
     char texte[100];
     struct tm date_de_publication;
     Auteur auteur;
     Rubrique rubrique;
     int id;//identifiant unique
     // Si le message est une réponse, stocker l'ID du message auquel il répond
     int reponse_msg_id;
}Message;




struct Cellule_auteur{
    Auteur aut;
    struct Cellule_auteur* suivant;
};
typedef struct Cellule_auteur* liste_aut;

struct Cellule_rubrique{
    Rubrique rub;
    struct Cellule_rubrique* suivant;
};
typedef struct Cellule_rubrique* liste_rub;

struct Cellule_forum{
    Forum f;
    struct Cellule_forum* suivant;
};
typedef struct Cellule_forum* liste_forum;

struct Cellule_message{
    Message msg;
    struct Cellule_message* suivant;
};
typedef struct Cellule_message* liste_msg;

struct Cellule_profil{
    Profil prof;
    struct Cellule_profil* suivant;
};
typedef struct Cellule_profil* liste_prof;

struct Cellule_lien_rub{
    char data_lien[60];
    struct Cellule_lien_rub* suivant;
};
typedef struct Cellule_lien_rub* liste_lien_rub;




