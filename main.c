#include <stdio.h>
#include"structure.h"
#include<stdlib.h>
#include <string.h>
  void free_liste_lien(liste_lien_rub llien);
  liste_lien_rub ajouter_lien(liste_lien_rub llien, char lien[]);
  Auteur rechercher_pseudo(liste_aut la,char p[]);
  void afficher_pseudo(liste_aut la);
  Profil rechercher_num(liste_prof lp,int num );
  void afficher_theme_rub(liste_rub lr);
  int trouver_rub(liste_rub lr,char theme[50]);
 //fonctions de saisie
    Forum saisie_forum();
    Rubrique saisie_rubrique();
    Message saisie_message(int *compt_id_msg,liste_msg lm,liste_rub lr,liste_aut la);
    Auteur saisie_auteur(liste_prof lp);
    Profil saisie_profil();
    //fonctions d'affichage
    void afficher_rubrique(Rubrique rub);
    void afficher_forum(Forum f);
    void afficher_message(Message m);
    void afficher_auteur(Auteur a);
    void afficher_profil(Profil p);
    //fonctions d'ajout dans une liste chainée
    liste_aut ajouter_auteur(liste_aut la,Auteur aut);
    liste_rub ajouter_rub(liste_rub lr,Rubrique rub);
    liste_forum ajouter_forum(liste_forum lf,Forum f);
    liste_msg ajouter_msg(liste_msg lm,Message msg);
    liste_prof ajouter_prof(liste_prof lp,Profil prof);
    //fonctions d'affichage des listes chainées
    void afficher_liste_auteur(liste_aut la);
    void afficher_liste_rub(liste_rub lr);
    void afficher_liste_forum(liste_forum lf);
    void afficher_liste_msg(liste_msg lm);
    void afficher_liste_prof(liste_prof lp);




//fonction de saisir du forum
Forum saisie_forum(){
    Forum f;
    printf("\t\t\tsaisir adresse internet:\n");
    scanf("\t\t\t%s",f.adresse_internet);
    printf("\t\t\tsaisir courriel:\n");
    scanf("\t\t\t%s",f.courriel);
    printf("\t\t\tsaisir nombre de rubriques:\n");
    scanf("\t\t\t   %d",&f.nbre_rub);


    return(f);}
//fonction de saisir du rubrique
Rubrique saisie_rubrique(){
    Rubrique rub;

    printf("\t\t\tsaisir theme:\n");
    scanf("\t\t\t%s",rub.theme);
    printf("\t\t\tsaisir annee de creation:\n");
    scanf("\t\t\t%d",&rub.date_de_creation.tm_year);
    printf("\t\t\tsaisir mois de creation:\n");
    scanf("\t\t\t%d",&rub.date_de_creation.tm_mon);
    printf("\t\t\tsaisir jour de creation:\n");
    scanf("\t\t\t%d",&rub.date_de_creation.tm_mday);
    printf("\t\t\tsaisir courriel:\n");
    scanf("\t\t\t%s",rub.courriel);
    printf("\t\t\tSaisir une liste de liens: \n");
    char lien[100];
    rub.liste_lien = NULL; // Initialisation de la liste de liens

    while (1) {
        printf("\t\t\tVeuillez entrer un lien. Pour terminer, appuyez sur 'Q': ");
        scanf("%s", lien);

        if (strcmp(lien, "Q") == 0) {
            break; // Sortie de la boucle si 'Q' est entré
        } else {
            rub.liste_lien = ajouter_lien(rub.liste_lien, lien); // Ajout  le lien
        }
    }

    return(rub);}

//fonction de saisir du message
Message saisie_message(int *compt_id_msg,liste_msg lm,liste_rub lr,liste_aut la){
    Auteur aut;
    Message msg;
    int rep;
    //identificateur message
    msg.id=*compt_id_msg;

    if(lr){
    afficher_theme_rub(lr);}
    else{
        printf("\t\t\t\taucun rubrique trouv%c",130);
        msg.id=-1;
        return msg;
    }

    printf("\t\t\tChoisisez l'un des themes des rubriques :\n");
    scanf("\t\t\t%s",msg.rubrique.theme);

    if(trouver_rub(lr,msg.rubrique.theme)==1){// il y'a le theme choisis
    printf("\t\t\tsi c'est une reponse,tapez 1 sinon 0:\n");
    scanf("\t\t\t%d",&rep);
     if (!rep){

           *compt_id_msg=*compt_id_msg+1;
            //n'est pas une réponse
            msg.reponse_msg_id=0;
    }
    else{

            if (lm!=NULL){//C'est une réponse et il y'a le messsage original
                *compt_id_msg=*compt_id_msg+1;
            printf("\t\t\tTapez le numero du message original\n");
            afficher_liste_msg(lm); //Chacun affiché avec son id
            scanf("\t\t\t%d",&msg.reponse_msg_id);}

            else{//C'est une réponse w il n y'a pas le messsage original
                printf("\t\t\til n'y a aucun message pour repondre a !");
                msg.id=-1;
                return msg;
            }

    }
    char p[50];

    if(la){
    printf("\t\t\tVoici les pseudos trouv%c\n",130);
    afficher_pseudo(la);
    printf("\t\t\t tapez votre pseudo\n");
    scanf("\t\t\t%s",p);

    aut=rechercher_pseudo(la,p);
    if(strcmp(aut.pseudo,"-1")==0){
         msg.id=-1;
         return msg;
    }

    strcpy(msg.auteur.pseudo,p);
    printf("\t\t\tsaisir titre:\n");
    scanf("\t\t\t%s",msg.titre);
    printf("\t\t\tsaisir texte:\n");
    scanf("\t\t\t%s",msg.texte);
    printf("\t\t\tsaisir annee de publication:\n");
    scanf("\t\t\t%d",&msg.date_de_publication.tm_year);
    printf("\t\t\tsaisir mois de publication:\n");
    scanf("\t\t\t%d",&msg.date_de_publication.tm_mon);
    printf("\t\t\tsaisir jour de publication:\n");
    scanf("\t\t\t%d",&msg.date_de_publication.tm_mday);
    return(msg);}
    else{
        printf("aucun auteur\n");
        msg.id=-1;
         return msg;}

    }

    else{// il n'ya pas le theme choisis
        printf("\t\t\til n'ya aucun rubrique de theme %s\n",msg.rubrique.theme);
         msg.id=-1;

         return msg;

    }
    }
//fonction de saisir d'un auteur
 Auteur saisie_auteur(liste_prof lp){
    Auteur aut;
    printf("\t\t\tsaisir pseudo:\n");
    scanf("\t\t\t%s",aut.pseudo);
    printf("\t\t\tsaisir annee du premier message:\n");
    scanf("\t\t\t%d",&aut.date_premier_msg.tm_year);
    printf("\t\t\tsaisir mois du premier message:\n");
    scanf("\t\t\t%d",&aut.date_premier_msg.tm_mon);
    printf("\t\t\tsaisir jour du premier message:\n");
    scanf("\t\t\t%d",&aut.date_premier_msg.tm_mday);
    printf("\t\t\tsaisir annee du dernier message:\n");
    scanf("\t\t\t%d",&aut.date_dernier_msg.tm_year);
    printf("\t\t\tsaisir mois du dernier message:\n");
    scanf("\t\t\t%d",&aut.date_dernier_msg.tm_mon);
    printf("\t\t\tsaisir jour du dernier message:\n");
    scanf("\t\t\t%d",&aut.date_dernier_msg.tm_mday);
    printf("\t\t\tsaisir nombre de messages:\n");
    scanf("\t\t\t%d",&aut.nombre_msg);
    char r;
    printf("veux tu avoir un profil ? taper o si oui sinon n\n");
    scanf(" %c",&r);
    if(r=='o'||r=='O'){
        if(lp){
        afficher_liste_prof(lp);
        int num;
        printf("choisissez un profil. Entrer le numero d'inscription\n");
        scanf("%d",&num);

         Profil p =rechercher_num(lp,num);
        aut.profil=p;}
        else{
            printf("Aucun profil trouv%c",130);
        }}else {

        aut.profil.num_inscription = -1;
    }



    return(aut);}
//fonction de saisir d'un profil
Profil saisie_profil(){
    Profil prof;
    printf("\t\t\tsaisir annee de naissnace:\n");
    scanf("\t\t\t%d",&prof.date_de_naissance.tm_year);
    printf("\t\t\tsaisir mois de naissnace:\n");
    scanf("\t\t\t%d",&prof.date_de_naissance.tm_mon);
    printf("\t\t\tsaisir jour de naissnace:\n");
    scanf("\t\t\t%d",&prof.date_de_naissance.tm_mday);
    printf("\t\t\tsaisir numero de telephone:\n");
    scanf("\t\t\t%ld",&prof.numero_telephone);
    printf("\t\t\tsaisir nom:\n");
    scanf("\t\t\t%s",prof.nom);
    printf("\t\t\tsaisir prenom:\n");
    scanf("\t\t\t%s",prof.prenom);
    printf("\t\t\tsaisir numero d'inscription:\n");
    scanf("\t\t\t%d",&prof.num_inscription);
    printf("\t\t\tsaisir votre adresse:\n");
    scanf("\t\t\t%s",prof.adresse);
    printf("\t\t\tsaisir courriel:\n");
    scanf("\t\t\t%s",prof.courriel);
    return(prof);}


//fonction d'affichage d'un rubrique
void afficher_rubrique(Rubrique rub){

 printf("\t\t\tvotre theme:%s\n",rub.theme);
 printf("\t\t\tvotre courriel:%s\n",rub.courriel);
 printf("\t\t\tvotre date de creation:%d/%d/%d\n",
        rub.date_de_creation.tm_mday,rub.date_de_creation.tm_mon,rub.date_de_creation.tm_year);

    printf("\t\t\tListe de liens:\n");
    liste_lien_rub parc = rub.liste_lien;
    while (parc != NULL) {
        printf("\t\t\t- %s\n", parc->data_lien);
        parc = parc->suivant;
    }
}
//fonction d'affichage d'un forum
void afficher_forum(Forum f){
 printf("\t\t\tvotre adresse internet:%s\n",f.adresse_internet);
 printf("\t\t\tvotre courriel:%s\n",f.courriel);
 printf("\t\t\tNombre de rubriques: %d\n", f.nbre_rub);


 }

//fonction d'affichage d'un message
void afficher_message(Message m){
    if(m.id!=-1){
printf("\t\t\tMessage %ccrit par:%s\n",130,m.auteur.pseudo);
printf("\t\t\tRubrique associ%ce:%s\n" ,130,m.rubrique.theme);
printf("\t\t\t%d:votre titre:%s\n",m.id,m.titre);
printf("\t\t\tvotre texte:%s\n",m.texte);
printf("\t\t\tvotre date de publication:%d/%d/%d\n"
       ,m.date_de_publication.tm_mday,m.date_de_publication.tm_mon,m.date_de_publication.tm_year);}

}
//fonction d'affichage d'un auteur
void afficher_auteur(Auteur a){
    if(strcmp(a.pseudo,"-1")!=0){
printf("\t\t\tvotre pseudo:%s\n",a.pseudo);
printf("\t\t\tvotre message:%d\n",a.nombre_msg);
printf("\t\t\tvotre date du premier message:%d/%d/%d\n",a.date_premier_msg.tm_mday,a.date_premier_msg.tm_mon,a.date_premier_msg.tm_year);
printf("\t\t\tvotre date du dernier message:%d/%d/%d\n",a.date_dernier_msg.tm_mday,a.date_dernier_msg.tm_mon,a.date_dernier_msg.tm_year);
printf("\t\t\tProfil associe:\n");
if(a.profil.num_inscription!=-1){
    afficher_profil(a.profil);
}
}

}

//fonction d'affichage d'un profil
void afficher_profil(Profil p){
    if(p.num_inscription != -1){
printf("\t\t\tvotre numero d'inscription:%d\n",p.num_inscription);
printf("\t\t\tvotre nom:%s\n",p.nom);
printf("\t\t\tvotre prenom:%s\n",p.prenom);
printf("\t\t\tvotre adresse:%s\n",p.adresse);
printf("\t\t\tvotre courriel:%s\n",p.courriel);
printf("\t\t\tvotre numero de telephone:%ld\n",p.numero_telephone);
printf("\t\t\tvotre date de naissance:%d/%d/%d\n",p.date_de_naissance.tm_mday,p.date_de_naissance.tm_mon,p.date_de_naissance.tm_year);
}}
// fonction d'ajout des auteurs dans une liste
liste_aut ajouter_auteur(liste_aut la,Auteur aut)
{
 struct Cellule_auteur *nouv, *parc;
 nouv = (struct Cellule_auteur*) malloc(sizeof(struct Cellule_auteur));
 nouv->aut=aut;
 nouv->suivant=NULL;
 if(la==NULL){
   la=nouv;}
 else{
  parc=la;
  while(parc->suivant!=NULL){
    parc=parc->suivant;}
    parc->suivant = nouv;
   }
 return(la);
}

// affichage liste contenant des auteurs
void afficher_liste_auteur(liste_aut la)
{
struct Cellule_auteur* tmp=la;
if(la==NULL){
    printf("\t\t\tla liste est vide");}

else{
  while (tmp!=NULL)
  {  afficher_auteur(tmp->aut);

     tmp=tmp->suivant;}}
}
//affichage des pseudos
void afficher_pseudo(liste_aut la)
{
struct Cellule_auteur* tmp=la;
if(la==NULL){
    printf("\t\t\tla liste est vide");}

else{
  int i=1;
  while (tmp!=NULL)
  {  printf("%d:%s\n",i,tmp->aut.pseudo);
     i++;

     tmp=tmp->suivant;}}
}

//fonction d'ajout des rubriques
liste_rub ajouter_rub(liste_rub lr,Rubrique rub)
{
 struct Cellule_rubrique *nouv, *parc;
 nouv = (struct Cellule_rubrique*) malloc(sizeof(struct Cellule_rubrique));
 nouv->rub=rub;
 nouv->suivant=NULL;
 if(lr==NULL){
   lr=nouv;}
 else{
  parc=lr;
  while(parc->suivant!=NULL){
    parc=parc->suivant;}
    parc->suivant = nouv;
   }
 return(lr);
}

// affichage liste contenant des rubriques
void afficher_liste_rub(liste_rub lr)
{
struct Cellule_rubrique* tmp=lr;
if(lr==NULL){
    printf("\t\t\tla liste est vide");}

else{
  while (tmp!=NULL)
  {  afficher_rubrique(tmp->rub);

     tmp=tmp->suivant;}}
}
//fonction d'affichage des themes
void afficher_theme_rub(liste_rub lr)
{
struct Cellule_rubrique* tmp=lr;
  int i=1;
  while (tmp!=NULL)
  {  printf("\t\t\ttheme %d:%s\n",i,tmp->rub.theme);
     i+=1;
     tmp=tmp->suivant;}}


//fonction d'ajout des forums
liste_forum ajouter_forum(liste_forum lf,Forum f)
{
 struct Cellule_forum *nouv, *parc;
 nouv = (struct Cellule_forum*) malloc(sizeof(struct Cellule_forum));
 nouv->f=f;
 nouv->suivant=NULL;
 if(lf==NULL){
   lf=nouv;}
 else{
  parc=lf;
  while(parc->suivant!=NULL){
    parc=parc->suivant;}
    parc->suivant = nouv;
   }
 return(lf);
}

// affichage liste contenant des forums
void afficher_liste_forum(liste_forum lf)
{
struct Cellule_forum* tmp=lf;
if(lf==NULL){
    printf("\t\t\tla liste est vide");}

else{
  while (tmp!=NULL)
  {  afficher_forum(tmp->f);

     tmp=tmp->suivant;}}
}

//fonction d'ajout des messages
liste_msg ajouter_msg(liste_msg lm,Message msg)
{
 struct Cellule_message *nouv, *parc;
 nouv = (struct Cellule_message*) malloc(sizeof(struct Cellule_message));
 nouv->msg=msg;
 nouv->suivant=NULL;
 if(lm==NULL){
   lm=nouv;}
 else{
  parc=lm;
  while(parc->suivant!=NULL){

    parc=parc->suivant;}
    parc->suivant = nouv;
   }
 return(lm);
}

// affichage liste contenant des messages
void afficher_liste_msg(liste_msg lm)
{
struct Cellule_message* tmp=lm;
if(lm==NULL){
    printf("\t\t\tla liste est vide");}

else{
  while (tmp!=NULL)
  {  afficher_message(tmp->msg);

     tmp=tmp->suivant;}}
}
//fonction d'ajout des profils
liste_prof ajouter_prof(liste_prof lp,Profil prof)
{
 struct Cellule_profil *nouv, *parc;
 nouv = (struct Cellule_profil*) malloc(sizeof(struct Cellule_profil));
 nouv->prof=prof;
 nouv->suivant=NULL;
 if(lp==NULL){
   lp=nouv;}
 else{
  parc=lp;
  while(parc->suivant!=NULL){
    parc=parc->suivant;}
    parc->suivant = nouv;
   }
 return(lp);
}
//fonction pour rechercher un profil a partir du numero d'inscription
Profil rechercher_num(liste_prof lp,int num )
{

  struct Cellule_profil* tmp=lp;

  while(tmp!=NULL){
   if(tmp->prof.num_inscription==num){
    return (tmp->prof);}
   tmp=tmp->suivant;
     }
    printf("\t\t\tLe numero d'inscription n'existe pas\n");
     Profil defaultProf;
     defaultProf.num_inscription = -1;
     return defaultProf;
   }


// affichage liste contenant des profils
void afficher_liste_prof(liste_prof lp)
{
struct Cellule_profil* tmp=lp;
if(lp==NULL){
    printf("\t\t\tla liste est vide");}

else{
  while (tmp!=NULL)
  {  afficher_profil(tmp->prof);

     tmp=tmp->suivant;}}
}

//fonction pour supprimer liste forum
void free_liste_forum(liste_forum lf) {
    struct Cellule_forum* current = lf;
    while (current != NULL) {
        struct Cellule_forum* next = current->suivant;
        free(current);
        current = next;
    }
}
//fonction pour supprimer liste auteur
void free_liste_auteur(liste_aut la) {
    struct Cellule_auteur* current = la;
    while (current != NULL) {
        struct Cellule_auteur* next = current->suivant;
        free(current);
        current = next;
    }
}
//fonction pour supprimer liste profil
void free_liste_profil(liste_prof lp) {
    struct Cellule_profil* current = lp;
    while (current != NULL) {
        struct Cellule_profil* next = current->suivant;
        free(current);
        current = next;
    }
}
//fonction pour supprimer liste rubrique
void free_liste_rubrique(liste_rub lr) {
    struct Cellule_rubrique* current = lr;
    while (current != NULL) {
        struct Cellule_rubrique* next = current->suivant;
        free(current);
        current = next;
    }
}
//fonction pour supprimer liste message
void free_liste_message(liste_msg lm) {
    struct Cellule_message* current = lm;
    while (current != NULL) {
        struct Cellule_message* next = current->suivant;
        free(current);
        current = next;
    }
}
// lister reponses
void liste_reponse(Message m,liste_msg lm){
    struct Cellule_message *parc;
    parc=lm;
    while(parc!=NULL){
        if(parc->msg.reponse_msg_id==m.id){
            afficher_message(parc->msg);
            liste_reponse(parc->msg,lm);}
        parc=parc->suivant;
        }
    }
//fonction pour rechercher le message a partir le l'ID
Message trouver_id(liste_msg lm,int id){

  struct Cellule_message* tmp=lm;

  while(tmp!=NULL){
   if(tmp->msg.id==id){
    return (tmp->msg);}
   tmp=tmp->suivant;
     }
    printf("\t\t\tL'ID n'existe pas\n");
     Message defaultMsg;
     defaultMsg.id = -1;
     return defaultMsg;
   }

//fonction pour rechercher un auteur a partir du pseudo
Auteur rechercher_pseudo(liste_aut la,char p[]){

  struct Cellule_auteur* tmp=la;
  while(tmp!=NULL){
   if(strcmp(tmp->aut.pseudo,p)==0){
    return (tmp->aut);}
   tmp=tmp->suivant;
     }
    printf("\t\t\tLe pseudo n'existe pas\n");
     Auteur defaultAut;
     strcpy(defaultAut.pseudo ,"-1");
     return defaultAut;
   }
//fonction pour rechercher le message a partir du theme
int trouver_rub(liste_rub lr,char theme[50]){
  struct Cellule_rubrique* parc_rub = lr;
   // Chercher la rubrique avec le theme donné
    while (parc_rub != NULL && strcmp(parc_rub->rub.theme, theme) != 0) {
        parc_rub = parc_rub->suivant;
    }

    if (parc_rub == NULL) {
        printf("\t\t\tRubrique non trouvée.\n");
        return 0;
    }
    else{
        return 1;
    }

}
//fonction pour donner les messages d'un rubrique
void afficher_messages_rubrique(liste_msg lm, liste_rub lr, char theme[50]) {
    if (trouver_rub(lr,theme)==1){
    struct Cellule_message* parc_msg = lm;

    // Afficher les messages de la rubrique
   int i=0;
    while (parc_msg != NULL) {

        if (strcmp(parc_msg->msg.rubrique.theme, theme) == 0) {
            afficher_message(parc_msg->msg);
            i+=1;
        }
        parc_msg = parc_msg->suivant;


   }

   if(i==0){
   printf("\t\t\til y'a aucun message dans le rubrique donee\n ");}}

}
 // fonction pour ajouter un lien à une liste chaînée
liste_lien_rub ajouter_lien(liste_lien_rub llien, char lien[]) {
    struct Cellule_lien_rub *nouv, *parc;
    nouv = (struct Cellule_lien_rub*) malloc(sizeof(struct Cellule_lien_rub));

    if (nouv == NULL) {
        printf("Allocation de mémoire échouée.");
        return llien; // Retourne la liste inchangée si l'allocation échoue
    }

    strcpy(nouv->data_lien, lien);
    nouv->suivant = NULL;

    if (llien == NULL) {
        llien = nouv;
    } else {
        parc = llien;
        while (parc->suivant != NULL) {
            parc = parc->suivant;
        }
        parc->suivant = nouv;
    }
    return llien;
}

// Fonction pour ecrire un message dans un fichier
void ecrire_message_fichier(Message msg, FILE *fp) {
   if(msg.id!=-1){
   fprintf(fp, "ID: %d, Titre: %s, Texte: %s, Date de publication: %d/%d/%d\n",
           msg.id, msg.titre, msg.texte, msg.date_de_publication.tm_mday,
            msg.date_de_publication.tm_mon, msg.date_de_publication.tm_year);}


}

// fonction pour ecrire liste des messages dans un fichier
void ecrire_liste_message_fichier(liste_msg lm, FILE *fp) {
     struct Cellule_message* tmp = lm;
    while (tmp != NULL) {

           ecrire_message_fichier(tmp->msg, fp);

        tmp = tmp->suivant;
    }
}

// Fonction pour lire les messages d'un fichier et les stocker dans une liste chainée
liste_msg lire_messages_fichier(FILE *fp) {
    liste_msg lm = NULL;
    Message msg;

    fscanf(fp, "-ID: %d,\tTitre: %s,\tTexte: %s,\tDate de publication: %d/%d/%d", &msg.id, msg.titre, msg.texte, &msg.date_de_publication.tm_mday, &msg.date_de_publication.tm_mon, &msg.date_de_publication.tm_year);
    lm = ajouter_msg(lm, msg);
    return lm;
}
// Fonction pour ecrire un forum dans un fichier
void ecrire_forum_fichier(Forum f, FILE *fp) {
    fprintf(fp, "Adresse Internet: %s, Courriel: %s, Nombre de rubriques: %d\n",
            f.adresse_internet, f.courriel, f.nbre_rub);
}

// fonction pour ecrire liste des forums dans un fichier
void ecrire_liste_forum_fichier(liste_forum lf, FILE *fp) {
    struct Cellule_forum* tmp = lf;
    while (tmp != NULL) {
        ecrire_forum_fichier(tmp->f, fp);
        tmp = tmp->suivant;
    }
}
// Fonction pour lire les forums d'un fichier et les stocker dans une liste chainée
liste_forum lire_forums_fichier(FILE *fp) {
    liste_forum lf = NULL;
    Forum f;

    fscanf(fp, "Adresse Internet: %s, Courriel: %s, Nombre de rubriques: %d",
           f.adresse_internet, f.courriel, &f.nbre_rub);
    lf = ajouter_forum(lf, f);

    return lf;
}
// Fonction pour ecrire un rubrique dans un fichier
void ecrire_rubrique_fichier(Rubrique rub, FILE *fp) {
    fprintf(fp, "Theme: %s, Courriel: %s, Date de creation: %d/%d/%d\n",
            rub.theme, rub.courriel, rub.date_de_creation.tm_mday,
            rub.date_de_creation.tm_mon, rub.date_de_creation.tm_year);

    liste_lien_rub parc_lien = rub.liste_lien;
    while (parc_lien != NULL) {
        fprintf(fp, "Lien: %s\n", parc_lien->data_lien);
        parc_lien = parc_lien->suivant;
    }
    fprintf(fp, "\n"); // ajout d'une ligne pour un autre rubrique
}

 // fonction pour ecrire liste des rubriques dans un fichier
void ecrire_liste_rubrique_fichier(liste_rub lr, FILE *fp) {
    struct Cellule_rubrique* tmp = lr;
    while (tmp != NULL) {
        ecrire_rubrique_fichier(tmp->rub, fp);
        tmp = tmp->suivant;
    }
}
// Fonction pour lire les rubriques d'un fichier et les stochker dans une liste chainée
liste_rub lire_rubriques_fichier(FILE *fp) {
    liste_rub lr = NULL;
    Rubrique rub;
    char ligne[256]; // Assume a maximum line length of 255 characters

    while (fgets(ligne, sizeof(ligne), fp) != NULL) {
        // Read the theme, courriel, and date_de_creation from the file
        sscanf(ligne, "Theme: %s, Courriel: %s, Date de creation: %d/%d/%d\n",
               rub.theme, rub.courriel, &rub.date_de_creation.tm_mday,
               &rub.date_de_creation.tm_mon, &rub.date_de_creation.tm_year);

        // Initialize the list of links
        rub.liste_lien = NULL;

        // Read the list of links from the file
        while (fgets(ligne, sizeof(ligne), fp) != NULL && ligne[0] != '\n') {
            char lien[100];
            sscanf(ligne, "Lien: %s", lien);
            rub.liste_lien = ajouter_lien(rub.liste_lien, lien);
        }

        lr = ajouter_rub(lr, rub);
    }

    return lr;
}
// Fonction pour ecrire un profil dans un fichier
void ecrire_profil_fichier(Profil p, FILE *fp) {
    if(p.num_inscription != -1){
   fprintf(fp,
 "numero d'inscription: %d, Nom: %s, Prenom: %s,Numero de telephone:%ld, Date de naissance: %d/%d/%d\n,Adresse:%s,Courriel:%s",
           p.num_inscription,p.nom,p.prenom,p.numero_telephone, p.date_de_naissance.tm_mday,
            p.date_de_naissance.tm_mon, p.date_de_naissance.tm_year,p.adresse,p.courriel);


}}

// fonction pour ecrire liste des profils dans un fichier
void ecrire_liste_profil_fichier(liste_prof lp, FILE *fp) {
     struct Cellule_profil* tmp = lp;
    while (tmp != NULL) {

           ecrire_profil_fichier(tmp->prof, fp);

        tmp = tmp->suivant;
    }
}

// Fonction pour lire les profils d'un fichier et les stocker dans une liste chainée
liste_prof lire_profils_fichier(FILE *fp) {
    liste_prof lp = NULL;
    Profil p;

    fscanf(fp, "numero d'inscription: %d, Nom: %s, Prenom: %s,Numero de telephone:%ld, Date de naissance: %d/%d/%d,Adresse:%s,Courriel:%s\n",
           &p.num_inscription,p.nom,p.prenom,&p.numero_telephone, &p.date_de_naissance.tm_mday,
           & p.date_de_naissance.tm_mon, &p.date_de_naissance.tm_year,p.adresse,p.courriel);
    lp= ajouter_prof(lp, p);
    return lp;
}
// Fonction pour ecrire un auteur dans un fichier
void ecrire_auteur_fichier(Auteur a, FILE *fp) {
   if(strcmp(a.pseudo,"-1")!=0){
   fprintf(fp, "pseudo:%s,votre message:%d,date du premier message:%d/%d/%d,date du dernier message:%d/%d/%d\n",a.pseudo,a.nombre_msg
           ,a.date_premier_msg.tm_mday,a.date_premier_msg.tm_mon,a.date_premier_msg.tm_year,a.date_dernier_msg.tm_mday,a.date_dernier_msg.tm_mon,a.date_dernier_msg.tm_year );

   }
}

// fonction pour ecrire liste des auteurs dans un fichier
void ecrire_liste_auteur_fichier(liste_aut la, FILE *fp) {
     struct Cellule_auteur* tmp = la;
    while (tmp != NULL) {

           ecrire_auteur_fichier(tmp->aut, fp);

        tmp = tmp->suivant;
    }
}

// Fonction pour lire les auteurs d'un fichier et les stocker dans une liste chainée
liste_aut lire_auteurs_fichier(FILE *fp) {
    liste_aut la = NULL;
    Auteur a;

    fscanf(fp, "pseudo:%s,votre message:%d,date du premier message:%d/%d/%d,date du dernier message:%d/%d/%d\n",a.pseudo,&a.nombre_msg
           ,&a.date_premier_msg.tm_mday,&a.date_premier_msg.tm_mon,&a.date_premier_msg.tm_year,&a.date_dernier_msg.tm_mday,&a.date_dernier_msg.tm_mon,&a.date_dernier_msg.tm_year);
    la = ajouter_auteur(la, a);
    return la;
}

//Afficher tous les messages du jour.
void Afficher_messages_jour(struct tm date,liste_msg lm){
     struct Cellule_message* tmp =lm;
   while(tmp!=NULL){
      if (tmp->msg.date_de_publication.tm_mday == date.tm_mday &&
            tmp->msg.date_de_publication.tm_mon == date.tm_mon &&
            tmp->msg.date_de_publication.tm_year == date.tm_year){
        return afficher_message(tmp->msg);
    }tmp=tmp->suivant;
   }
   printf("aucun message trouver en cette date");
}
//fonction Rechercher un mot dans un texte de messages
void Rechercher_mot(Message msg,char mot[]){
  if (strstr(msg.texte, mot) != NULL) {
        printf("Le mot \"%s\" a %ct%c trouv%c dans la cha%cne.\n", mot,130,130,130,'î');
    } else {
        printf("Le mot \"%s\" n'a pas %ct%c trouv%c dans la cha%cne.\n", mot,130,130,130,'î');
    }}
// fonction pour comparer deux messages selon date de publication
int compare_dates(const void *a, const void *b) {
    const Message *msg1 = (const Message *)a;
    const Message *msg2 = (const Message *)b;

    // comparer années
    if (msg1->date_de_publication.tm_year != msg2->date_de_publication.tm_year) {
        return msg1->date_de_publication.tm_year - msg2->date_de_publication.tm_year;
    }

    // Comparer mois
    if (msg1->date_de_publication.tm_mon != msg2->date_de_publication.tm_mon) {
        return msg1->date_de_publication.tm_mon - msg2->date_de_publication.tm_mon;
    }

    // Comparer jour
    return msg1->date_de_publication.tm_mday - msg2->date_de_publication.tm_mday;
}

// fonction pour afficher messages d'un rubrique dans un ordre chrono
void Afficher_messages_chrono(liste_msg lm, liste_rub lr, char theme[50]) {
    if (trouver_rub(lr, theme) == 1) {
        struct Cellule_message *messages_array = NULL;
        struct Cellule_message *parc_msg = lm;

        // compter les messages dans un rubrique
        int message_count = 0;
        while (parc_msg != NULL) {
            if (strcmp(parc_msg->msg.rubrique.theme, theme) == 0) {
                message_count++;
            }
            parc_msg = parc_msg->suivant;
        }

        // Allocation memoire pour tableau de messages
        messages_array = (struct Cellule_message *)malloc(message_count * sizeof(struct Cellule_message));

        // remplir tableau avec messaged'un rubrique
        parc_msg = lm;
        int i = 0;
        while (parc_msg != NULL) {
            if (strcmp(parc_msg->msg.rubrique.theme, theme) == 0) {
                messages_array[i++] = *parc_msg;
            }
            parc_msg = parc_msg->suivant;
        }

        // Sort tableau de messages a partir du date de pub
        qsort(messages_array, message_count, sizeof(struct Cellule_message), compare_dates);

        //afficher sorted messages
        for (i = 0; i < message_count; i++) {
            afficher_message(messages_array[i].msg);
        }

        // Free memoire alloué
        free(messages_array);
    } else {
        printf("Rubrique non trouv%ce.\n",130);
    }
}
// Fonction pour retrouver tous les messages d'un auteur (par son pseudo),
// ou d'un profil (à partir de son numéro d'inscription\n)
void Retrouve_messages_auteur_profil(liste_msg lm, liste_aut la, liste_prof lp) {
    int choix;
    printf("Choisir l'option:\n");
    printf("1. Retrouver messages par pseudo d'auteur\n");
    printf("2. Retrouver messages par numéro d'inscription de profil\n");
    scanf("%d", &choix);

    switch (choix) {
        case 1: {
            char pseudo[50];
            printf("Entrez le pseudo de l'auteur : ");
            scanf("%s", pseudo);
             Auteur aut;
             aut = rechercher_pseudo(la,pseudo);

            if(strcmp(aut.pseudo,"-1")!=0){
                struct Cellule_message *parc_msg = lm;

                    // Iteration list de messages pour touver message d'un auteur
                    while (parc_msg != NULL) {
                        if (strcmp(parc_msg->msg.auteur.pseudo,pseudo)==0) {

                            afficher_message(parc_msg->msg);
                        }
                        parc_msg = parc_msg->suivant;
                    }
        }

            break;
        }

        case 2: {
            int num_inscription;
            printf("Entrez le numéro d'inscription du profil : ");
            scanf("%d", &num_inscription);
            Profil prof;
            prof=rechercher_num(lp,num_inscription);
            if(prof.num_inscription!=-1){
                struct Cellule_message *parc_msg = lm;

                    // Iteration  list de messages pour trouver message d'un profil
                    while (parc_msg != NULL) {
                        if (parc_msg->msg.auteur.profil.num_inscription == num_inscription) {
                            afficher_message(parc_msg->msg);
                        }
                        parc_msg = parc_msg->suivant;
                    }


            }



            break;
        }

        default: {
            printf("Choix invalide.\n");
            break;
        }
    }
}
// Fonction pour récupérer tous les profils des personnes ayant posté dans une rubrique donnée
void Retrouver_profiles_par_rubrique(liste_msg lm, liste_rub lr, liste_prof lp, char theme[50]) {
    struct Cellule_rubrique* tmp_rubrique = lr;
    struct Cellule_message* tmp_message = lm;

    // Find the rubrique with the given theme
    while (tmp_rubrique != NULL && strcmp(tmp_rubrique->rub.theme, theme) != 0) {
        tmp_rubrique = tmp_rubrique->suivant;
    }

    // If the rubrique is found, retrieve profiles of people posting in that rubrique
    if (tmp_rubrique != NULL) {
        while (tmp_message != NULL) {
            if (strcmp(tmp_message->msg.rubrique.theme, theme) == 0) {
                // Find the profile with the matching num_inscription
                struct Cellule_profil* tmp_profil = lp;
                while ((tmp_profil != NULL )&&( tmp_profil->prof.num_inscription != tmp_message->msg.auteur.profil.num_inscription)) {
                    tmp_profil = tmp_profil->suivant;
                }

                // If the profile is found, print or process it as needed
                if (tmp_profil != NULL) {
                    printf("Profil trouvé: Numéro d'inscription %d, Nom: %s, Prénom: %s\n",
                           tmp_profil->prof.num_inscription, tmp_profil->prof.nom, tmp_profil->prof.prenom);
                }
            }
            tmp_message = tmp_message->suivant;
        }
    } else {
        printf("Rubrique non trouvée.\n");
    }
}




float moyenneNombreMessagesMemeAuteur(liste_aut la) {
    int totalMessages = 0;
    int totalAuteurs = 0;

    // Utiliser une variable temporaire pour itérer sur la liste des auteurs
    liste_aut temp = la;

    // Parcourir la liste des auteurs et compter le nombre total de messages
    while (temp != NULL) {

        totalMessages += temp->aut.nombre_msg;
        totalAuteurs++;

        temp = temp->suivant;
    }

    // Vérifier si le nombre d'auteurs est égal à zéro pour éviter la division par zéro
    if (totalAuteurs == 0) {
        printf("Il n'y a pas d'auteurs dans la liste.\n");
        return 0.0; // Retourner 0 pour éviter la division par zéro
    }

    // Calculer la moyenne du nombre de messages par auteur

    float moyenne = (float)totalMessages / totalAuteurs;
    printf("1\n");
      printf("La moyenne du nombre de messages par auteur est : %.2f\n", moyenne);
    return moyenne;
}

// Structure pour stocker la date et le nombre de messages pour cette date
typedef struct {
    struct tm date;
    int count;
} DateCount;

// Fonction pour compter le nombre de messages par date de publication
void compterMessagesParDate(liste_msg messages) {
    // Initialiser un dictionnaire pour stocker les dates et le nombre de messages associés
    DateCount dateCount[100]; // Nombre maximal de dates (à adapter selon vos besoins)
    int datesCounted = 0;

    // Parcourir la liste de messages
    while (messages != NULL) {
        int dateFound = 0;
        // Vérifier si la date du message est déjà présente dans le dictionnaire
        for (int i = 0; i < datesCounted; ++i) {
            if (memcmp(&messages->msg.date_de_publication, &dateCount[i].date, sizeof(struct tm)) == 0) {
                // La date existe déjà, incrémenter le compteur pour cette date
                dateCount[i].count++;
                dateFound = 1;
                break;
            }
        }

        // Si la date n'a pas été trouvée, l'ajouter au dictionnaire
        if (!dateFound) {
            memcpy(&dateCount[datesCounted].date, &messages->msg.date_de_publication, sizeof(struct tm));
            dateCount[datesCounted].count = 1;
            datesCounted++;
        }

        messages = messages->suivant;
    }

    // Afficher le nombre de messages pour chaque date
    printf("Nombre de messages par date de publication :\n");
    for (int i = 0; i < datesCounted; ++i) {
        printf("%d-%02d-%02d : %d messages\n", dateCount[i].date.tm_year + 1900, dateCount[i].date.tm_mon + 1, dateCount[i].date.tm_mday, dateCount[i].count);
    }
}

// Fonction pour déterminer le jour le plus fréquenté de la semaine
void jourLePlusFrequente(liste_msg lm) {
    int nombreParJour[7]; // En supposant dimanche à samedi

    struct Cellule_message* courant = lm;
    while (courant != NULL) {
        int jourSemaine = courant->msg.date_de_publication.tm_wday;
        nombreParJour[jourSemaine]++;
        courant = courant->suivant;
    }

    int jourPlusFrequente = 0;
    for (int i = 1; i < 7; ++i) {
        if (nombreParJour[i] > nombreParJour[jourPlusFrequente]) {
            jourPlusFrequente = i;
        }
    }

    printf("Jour le plus fr%cquent%c de la semaine : %d\n",130,130, jourPlusFrequente);
}
// Fonction pour calculer le nombre de messages par rubrique
void messagesParRubrique(liste_msg lm, liste_rub lr) {
    struct Cellule_rubrique* rubriqueCourante = lr;
    while (rubriqueCourante != NULL) {
        int nombreMessagesRubrique = 0;

        struct Cellule_message* messageCourant = lm;
        while (messageCourant != NULL) {
            if (strcmp(messageCourant->msg.rubrique.theme, rubriqueCourante->rub.theme) == 0) {
                nombreMessagesRubrique++;
            }
            messageCourant = messageCourant->suivant;
        }

        printf("Rubrique de th%cme '%s' : %d messages\n",130, rubriqueCourante->rub.theme, nombreMessagesRubrique);

        rubriqueCourante = rubriqueCourante->suivant;
    }
}

// Fonction pour calculer la longueur moyenne des textes de messages
void longueurTexteMoyen(liste_msg lm) {
    int longueurTexteTotale = 0;
    int nombreMessages = 0;

    struct Cellule_message* courant = lm;
    while (courant != NULL) {
        longueurTexteTotale += strlen(courant->msg.texte);
        nombreMessages++;
        courant = courant->suivant;
    }

    if (nombreMessages > 0) {
        double longueurMoyenne = (double)longueurTexteTotale / nombreMessages;
        printf("Longueur moyenne du texte : %.2f caract%cres\n", longueurMoyenne,'è');
    }
}
// Fonction pour supprimer un forum de la liste
void supprimer_forum(liste_forum lf, char adresse_internet[]) {
    if (lf == NULL) {
        printf("La liste des forums est vide.\n");
        return;

    }

    struct Cellule_forum* tmp = lf;
    struct Cellule_forum* prev = NULL;

    // Rechercher le forum avec l'adresse internet donnée
    while (tmp != NULL && strcmp(tmp->f.adresse_internet, adresse_internet) != 0) {
        prev = tmp;
        tmp = tmp->suivant;
    }

    // Si le forum avec l'adresse internet donnée est trouvé, le supprimer
    if (tmp != NULL) {
        if (prev != NULL) {
            prev->suivant = tmp->suivant;
        } else {
            lf = tmp->suivant;
        }
        free(tmp);
        printf("Forum avec l'adresse internet %s supprim%c avec succ%cs.\n", adresse_internet,130,'è');
    } else {
        printf("Forum avec l'adresse internet %s non trouv%c.\n", adresse_internet,130);
    }

    return ;
}
// Fonction pour supprimer une rubrique de la liste
void supprimer_rubrique(liste_rub lr, char theme[]) {
    if (lr == NULL) {
        printf("La liste des rubriques est vide.\n");
        return ;
    }

    struct Cellule_rubrique* tmp = lr;
    struct Cellule_rubrique* prev = NULL;

    // Rechercher la rubrique avec le thème donné
    while (tmp != NULL && strcmp(tmp->rub.theme, theme) != 0) {
        prev = tmp;
        tmp = tmp->suivant;
    }

    // Si la rubrique avec le thème donné est trouvée, la supprimer
    if (tmp != NULL) {
        if (prev != NULL) {
            prev->suivant = tmp->suivant;
        } else {
            lr = tmp->suivant;
        }
        free_liste_lien(tmp->rub.liste_lien);
        free(tmp);
        printf("Rubrique avec le th%cme %s supprim%c avec succ%cs.\n",'è', theme,130,'è');
    } else {
        printf("Rubrique avec le th%cme %s non trouv%ce.\n",'è', theme,130);
    }

    return ;
}
void supprimer_profil(liste_prof lp, long num_inscription) {
    if (lp == NULL) {
        printf("La liste des profils est vide.\n");
        return ;
    }

    struct Cellule_profil* tmp = lp;
    struct Cellule_profil* prev = NULL;

    // Rechercher le profil avec le numéro d'inscription donné
    while (tmp != NULL && tmp->prof.num_inscription != num_inscription) {
        prev = tmp;
        tmp = tmp->suivant;
    }

    // Si le profil avec le numéro d'inscription donné est trouvé, le supprimer
    if (tmp != NULL) {
        if (prev != NULL) {
            prev->suivant = tmp->suivant;
        } else {
            lp = tmp->suivant;
        }
        free(tmp);
        printf("Profil avec le num%cro d'inscription %ld supprim%c avec succ%cs.\n",130,num_inscription,130,'è');
    } else {
        printf("Profil avec le num%cro d'inscription %ld non trouv%c.\n",130, num_inscription,130);
    }

    return ;
}
void supprimer_auteur(liste_aut la, char pseudo[]) {
    if (la == NULL) {
        printf("La liste des auteurs est vide.\n");
        return;
    }

    struct Cellule_auteur* tmp = la;
    struct Cellule_auteur* prev = NULL;

    // Rechercher l'auteur avec le pseudo donné
    while (tmp != NULL && strcmp(tmp->aut.pseudo, pseudo) != 0) {
        prev = tmp;
        tmp = tmp->suivant;
    }

    // Si l'auteur avec le pseudo donné est trouvé, le supprimer
    if (tmp != NULL) {
        if (prev != NULL) {
            prev->suivant = tmp->suivant;
        } else {
            la = tmp->suivant;
        }
        free(tmp);
        printf("Auteur avec le pseudo %s supprim%c avec succ%cs.\n", pseudo,130,'è');
    } else {
        printf("Auteur avec le pseudo %s non trouv%c.\n", pseudo,130);
    }

    return ;
}
void supprimer_message(liste_msg lm, int id) {
    if (lm == NULL) {
        printf("La liste des messages est vide.\n");
        return ;
    }

    struct Cellule_message* tmp = lm;
    struct Cellule_message* prev = NULL;

    // Rechercher le message avec l'ID donné
    while (tmp != NULL && tmp->msg.id != id) {
        prev = tmp;
        tmp = tmp->suivant;
    }

    // Si le message avec l'ID donné est trouvé, le supprimer
    if (tmp != NULL) {
        if (prev != NULL) {
            prev->suivant = tmp->suivant;
        } else {
            lm = tmp->suivant;
        }
        free(tmp);
        printf("Message avec l'ID %d supprim%c avec succ%cs.\n", id,130,'è');

    } else {
        printf("Message avec l'ID %d non trouv%c.\n", id,130);
    }

    return;
}

void supprimer(liste_forum lf,liste_rub lr,liste_prof lp,liste_aut la,liste_msg lm){
 int choix;
     printf("\t\t\t\t~~1.forum~~\n");
     printf("\t\t\t\t~~2.rubrique~~\n");
     printf("\t\t\t\t~~3.profil~~\n");
     printf("\t\t\t\t~~4.auteur~~\n");
     printf("\t\t\t\t~~5.message~~\n");
     printf("\n\n\t\t\t\t votre choix:");
     scanf("%d",&choix);
  switch(choix) {
     case 1:{
      char adresse[50];
      printf("\t\t\t\tdonner l'adresse internet:\n ");
      scanf("%s",adresse);
      supprimer_forum(lf,adresse);

      break;

     }
      case 2:{
      char theme[50];
      printf("\t\t\t\tdonner theme:\n ");
      scanf("%s",theme);
      supprimer_rubrique(lr,theme);

      break;

     }
    case 3:{
      long num;
      printf("\t\t\t\tdonner numero d'inscription:\n ");
      scanf("%ld",&num);
      supprimer_profil(lp,num);

      break;

     }
     case 4:{
      char pseudo[50];
      printf("\t\t\t\tdonner pseudo:\n ");
      scanf("%s",pseudo);
      supprimer_auteur(la,pseudo);


      break;

     }
      case 5:{
      int id;
      printf("\t\t\t\tdonner id:\n ");
      scanf("%d",&id);
      supprimer_message(lm,id);


      break;
   }
  default:{
            printf("choix invalide. Veuillez choisir une option valide.\n");
        }



}
}
// Fonction pour modifier un forum dans la liste
void modifier_forum(liste_forum lf, char adresse[]) {

    if (lf == NULL) {
        printf("La liste des forums est vide.\n");
        return;

    }

    struct Cellule_forum* tmp = lf;

    // Rechercher le forum avec l'adresse internet
    while (tmp != NULL && strcmp(tmp->f.adresse_internet, adresse) != 0) {
        tmp = tmp->suivant;
    }

    // Si le forum avec l'adresse donné est trouvé, effectuer les modifications
    if (tmp != NULL) {
        // Effectuer les modifications nécessaires, par exemple, demander à l'utilisateur de fournir de nouvelles données
        printf("Modifier le forum avec l'adresse internet %s :\n", adresse);

        //  Demander une nouvelle adresse internet
        printf("Nouvelle adresse internet : ");
        scanf("%s", tmp->f.adresse_internet);
        printf("Nouvelle courriel : ");
        scanf("%s", tmp->f.courriel);
        printf("Nouveau nombre des rubriques: ");
        scanf("%d", &tmp->f.nbre_rub);





    } else {
        printf("Forum avec l'adresse internet %s non trouv%c.\n", adresse,130);
    }

    return ;
}
// Fonction pour libérer la mémoire d'une liste de liens
void free_liste_lien(liste_lien_rub llien) {
    struct Cellule_lien_rub* current = llien;
    while (current != NULL) {
        struct Cellule_lien_rub* next = current->suivant;
        free(current);
        current = next;
    }
}
// Fonction pour modifier une rubrique dans la liste
void modifier_rubrique(liste_rub lr, char theme[50]) {
    if (lr == NULL) {
        printf("La liste des rubriques est vide.\n");
        return ;
    }

    struct Cellule_rubrique* tmp = lr;

    // Rechercher la rubrique avec le thème donné
    while (tmp != NULL && strcmp(tmp->rub.theme, theme) != 0) {
        tmp = tmp->suivant;
    }

    // Si la rubrique avec le thème donné est trouvée, effectuer les modifications
    if (tmp != NULL) {
        // demander à l'utilisateur de fournir de nouveaux données
        printf("Modifier la rubrique avec le th%cme %s :\n",'è',theme);

        printf("Nouveau theme : ");
        scanf("%s", tmp->rub.theme);
        printf("Nouvelle adresse courriel : ");
        scanf("%s", tmp->rub.courriel);
        printf("Nouveau date de creation sous forme --/--/-- : ");
        scanf("%d/%d/%d",&tmp->rub.date_de_creation.tm_mday,&tmp->rub.date_de_creation.tm_mon,&tmp->rub.date_de_creation.tm_year);
         // Supprimer l'ancienne liste de liens
        free_liste_lien(tmp->rub.liste_lien);

        char lien[100];
        tmp->rub.liste_lien = NULL; // Initialisation de la liste de liens

        while (1) {
        printf("\t\t\tVeuillez entrer nouveau lien. Pour terminer, appuyez sur 'Q': ");
        scanf("%s", lien);

        if (strcmp(lien, "Q") == 0) {
            break; // Sortie de la boucle si 'Q' est entré
        } else {
            tmp->rub.liste_lien = ajouter_lien(tmp->rub.liste_lien, lien); // Ajout  le lien
        }
    }



        printf("Rubrique avec le th%cme %s modifi%ce avec succ%cs.\n",'è', theme,130,130);
    } else {
        printf("Rubrique avec le th%cme %s non trouv%Ce.\n",'è', theme,130);
    }

    return ;
}

// Fonction pour modifier un profil dans la liste
void modifier_profil(liste_prof lp, long int num_inscription) {
    if (lp == NULL) {
        printf("La liste des profils est vide.\n");
        return;
    }

    struct Cellule_profil* tmp = lp;

    // Rechercher le profil avec le numéro d'inscription donné
    while (tmp != NULL && tmp->prof.num_inscription != num_inscription) {
        tmp = tmp->suivant;
    }

    // Si le profil avec le numéro d'inscription donné est trouvé, effectuer les modifications
    if (tmp != NULL) {
        // demander à l'utilisateur de fournir de nouveaux données
        printf("Modifier le profil avec le num%cro d'inscription %ld :\n",130, num_inscription);

        printf("Nouvelle date de naissance sous forme --/--/-- : ");
        scanf("%d/%d/%d", &(tmp->prof.date_de_naissance.tm_mday), &(tmp->prof.date_de_naissance.tm_mon), &(tmp->prof.date_de_naissance.tm_year));
        printf("Nouveau num%cro de t%cl%cphone : ",130,130,130);
        scanf("%ld", &(tmp->prof.numero_telephone));
        printf("Nouveau nom : ");
        scanf("%s", tmp->prof.nom);
        printf("Nouveau pr%cnom : ",130);
        scanf("%s", tmp->prof.prenom);
        printf("Nouveau num%cro d'inscription : ",130);
        scanf("%d", &(tmp->prof.num_inscription));
        printf("Nouvelle adresse : ");
        scanf("%s", tmp->prof.adresse);
        printf("Nouveau courriel : ");
        scanf("%s", tmp->prof.courriel);

        printf("Profil avec le num%cro d'inscription %ld modifi%c avec succ%cs.\n",130, num_inscription,130,'è');
    } else {
        printf("Profil avec le num%cro d'inscription %ld non trouv%c.\n",130, num_inscription,130);
    }
}

// Fonction pour modifier un auteur dans la liste
void modifier_auteur(liste_aut la, char pseudo[]) {
    if (la == NULL) {
        printf("La liste des auteurs est vide.\n");
        return;
    }

    struct Cellule_auteur* tmp = la;

    // Rechercher l'auteur avec le pseudo donné
    while (tmp != NULL && strcmp(tmp->aut.pseudo, pseudo) != 0) {
        tmp = tmp->suivant;
    }

    // Si l'auteur avec le pseudo donné est trouvé, effectuer les modifications
    if (tmp != NULL) {
        // demander à l'utilisateur de fournir de nouveaux données
        printf("Modifier l'auteur avec le pseudo %s :\n", pseudo);

        printf("Nouveau pseudo : ");
        scanf("%s", tmp->aut.pseudo);
        printf("Nouvelle date du premier message sous forme --/--/-- : ");
        scanf("%d/%d/%d", &(tmp->aut.date_premier_msg.tm_mday), &(tmp->aut.date_premier_msg.tm_mon), &(tmp->aut.date_premier_msg.tm_year));
        printf("Nouvelle date du dernier message sous forme --/--/-- : ");
        scanf("%d/%d/%d", &(tmp->aut.date_dernier_msg.tm_mday), &(tmp->aut.date_dernier_msg.tm_mon), &(tmp->aut.date_dernier_msg.tm_year));
        printf("Nouveau nombre de messages : ");
        scanf("%d", &(tmp->aut.nombre_msg));

        // Vous pouvez ajouter ici la modification du profil associé, si nécessaire

        printf("Auteur avec le pseudo %s modifi%c avec succ%cs.\n", pseudo,130,'è');
    } else {
        printf("Auteur avec le pseudo %s non trouv%c.\n", pseudo,130);
    }
}
// Fonction pour modifier un message dans la liste
void modifier_message(liste_msg lm, int id) {
    if (lm == NULL) {
        printf("La liste des messages est vide.\n");
        return;
    }

    struct Cellule_message* tmp = lm;

    // Rechercher le message avec l'ID donné
    while (tmp != NULL && tmp->msg.id != id) {
        tmp = tmp->suivant;
    }

    // Si le message avec l'ID donné est trouvé, effectuer les modifications
    if (tmp != NULL) {
        // demander à l'utilisateur de fournir de nouveaux données
        printf("Modifier le message avec l'ID %d :\n", id);

        printf("Nouveau titre : ");
        scanf("%s", tmp->msg.titre);
        printf("Nouveau texte : ");
        scanf("%s", tmp->msg.texte);
        printf("Nouvelle date de publication sous forme --/--/-- : ");
        scanf("%d/%d/%d", &(tmp->msg.date_de_publication.tm_mday), &(tmp->msg.date_de_publication.tm_mon), &(tmp->msg.date_de_publication.tm_year));

        printf("Message avec l'ID %d modifi%c avec succ%cs.\n", id,130,'è');
    } else {
        printf("Message avec l'ID %d non trouv%c.\n", id,130);
    }
}





void modifier(liste_forum lf,liste_rub lr,liste_prof lp,liste_aut la,liste_msg lm){
  int choix;
     printf("\t\t\t\t~~1.forum~~\n");
     printf("\t\t\t\t~~2.rubrique~~\n");
     printf("\t\t\t\t~~3.profil~~\n");
     printf("\t\t\t\t~~4.auteur~~\n");
     printf("\t\t\t\t~~5.message~~\n");
     printf("\n\n\t\t\t\t votre choix:");
     scanf("%d",&choix);
  switch(choix) {
     case 1:{
      char adresse[50];
      printf("\t\t\t\tdonner l'adresse internet:\n ");
      scanf("%s",adresse);
      modifier_forum(lf,adresse);



      break;

     }
      case 2:{
      char theme[50];
      printf("\t\t\t\tdonner theme:\n ");
      scanf("%s",theme);
      modifier_rubrique(lr,theme);

      break;

     }
    case 3:{
      long num;
      printf("\t\t\t\tdonner numero d'inscription:\n ");
      scanf("%ld",&num);
      modifier_profil(lp,num);

      break;

     }
     case 4:{
      char pseudo[50];
      printf("\t\t\t\tdonner pseudo:\n ");
      scanf("%s",pseudo);
      modifier_auteur(la,pseudo);


      break;

     }
      case 5:{
      int id;
      printf("\t\t\t\tdonner id:\n ");
      scanf("%d",&id);
      modifier_message(lm,id);


      break;
   }
  default:{
            printf("choix invalide. Veuillez choisir une option valide.\n");
        }



}
}


int main(){
//   menu
    int nb_rubrique=1;
    int nb_messages=1;

    liste_forum lf=NULL;
    liste_rub lr=NULL;
    liste_prof lp=NULL;
    liste_msg lm=NULL;
    liste_aut la=NULL;
    int choix;
    printf("\t\t\t******************salut!*******************\n");
    printf("\t\t\t**********Bienvenu dans le forum***********\n\n");
    printf("\t\t\t****SVP entrer l'un des choix****\n\n");


    do {
        printf("\n\t\t\t\t\t\t***Menu***\n");

        printf("\t\t\t\t~~Gestion forum~~\n");
        printf("\t\t\t\t\t 1.Ajout\n");
        printf("\t\t\t\t\t 2.afficher\n");

        printf("\t\t\t\t~~Gestion Rubrique~~\n");
        printf("\t\t\t\t\t 3.Ajouter \n");
        printf("\t\t\t\t\t 4.Afficher \n");
        printf("\t\t\t\t\t 12.lister les message a un rubrique donne%c:\n",130);

        printf("\t\t\t\t~~Gestion Profil~~\n");
        printf("\t\t\t\t\t 5.Ajouter\n");
        printf("\t\t\t\t\t 6.Afficher\n");
        printf("\t\t\t\t\t 17.Retrouver tous les profils de personnes\n\t\t\t\t\tqui postent dans une rubrique donn%ce\n",130);

        printf("\t\t\t\t~~Gestion Auteur~~\n");
        printf("\t\t\t\t\t 7.ajouter\n");
        printf("\t\t\t\t\t 8.afficher\n");

        printf("\t\t\t\t~~Gestion Message~~\n");
        printf("\t\t\t\t\t 9.ajouter \n");
        printf("\t\t\t\t\t 10.afficher\n");
        printf("\t\t\t\t\t 11.lister les r%cponses a un message donne%c:\n",130,130);
        printf("\t\t\t\t\t 13.Afficher tous les messages d'un jour.\n");
        printf("\t\t\t\t\t 14.Rechercher un mot dans un texte de messages.\n");
        printf("\t\t\t\t\t 15.Affiche les messages d'une rubrique par ordre \n \t\t\t\t\tchronologique de leur date de publication\n");
        printf("\t\t\t\t\t 16.Retrouver tous les messages d'un auteur (par son pseudo)\n\t\t\t\t\t, ou d'un profil (%c partir de son num%cro d'inscription)\n",224,130);

        printf("\t\t\t\t~~Statistiques~~\n");
        printf("\t\t\t\t\t 18.Le nombre de messages poste%cs en moyenne par un m%cme auteur\n",130,234);
        printf("\t\t\t\t\t 19.Le nombre de messages par date de publication\n");
        printf("\t\t\t\t\t 20.le jour le plus fr%cquent%c de la semaine\n",130,130);
        printf("\t\t\t\t\t 21.le nombre de messages par rubrique\n");
        printf("\t\t\t\t\t 22.la longueur moyenne des textes de messages\n");

        printf("\t\t\t\t~~Edition~~\n");
        printf("\t\t\t\t\t 23.Supprimer\n");
        printf("\t\t\t\t\t 24.Modifier\n");


        printf("\t\t\t\t\t\t 25.Quitter\n");
        printf("\n\n\t\t\t\t votre choix:");
        scanf("%d",&choix);

        switch(choix){
          case 1:{
              Forum f;
              f=saisie_forum();
              lf= ajouter_forum(lf,f);
              FILE *fp = fopen("forums.txt", "a"); // Open the file in append mode
              if (fp != NULL) {
                ecrire_forum_fichier(f, fp);
                fclose(fp); // Close the file after writing
             } else {
                printf("Le fichier n'a pas pu être ouvert pour ecrire.\n");
               }

                break;
              }
          case 2:{
            afficher_liste_forum(lf);
             // Read forums from the file and store them in a linked list
             FILE *fp = fopen("forums.txt", "r"); // Open the file in read mode
             if (fp != NULL) {
                 lire_forums_fichier(fp);
                 fclose(fp); // Close the file after reading
                  // Process the readForumList as needed
             } else {
                 printf("Le fichier n'a pas pu être ouvert pour lire.\n");
               }
                break;
          }
          case 3:{
            Rubrique rub;
             rub=saisie_rubrique(&nb_rubrique,lr);
            lr= ajouter_rub(lr,rub);
            FILE *rubrique_fp = fopen("rubriques.txt", "w");
            if (rubrique_fp != NULL) {
                   ecrire_liste_rubrique_fichier(lr, rubrique_fp);
                  fclose(rubrique_fp);
          } else {
                printf("Le fichier n'a pas pu être ouvert pour ecrire.\n");
            }
          break;
          }

          case 4:{
              afficher_liste_rub(lr);
              FILE *rubrique_fp_read = fopen("rubriques.txt", "r");
              if (rubrique_fp_read != NULL) {
                 lr = lire_rubriques_fichier(rubrique_fp_read);
                 fclose(rubrique_fp_read);
                 } else {
               printf("Le fichier n'a pas pu être ouvert pour lire.\n");
           }
           break;
          }

          case 5:{
           Profil prof;
              prof=saisie_profil();
              lp=ajouter_prof(lp,prof);
               FILE *fp = fopen("Profils.txt", "a"); // Open the file in append mode
              if (fp != NULL) {
                ecrire_profil_fichier(prof, fp);
                fclose(fp); // Close the file after writing
             } else {
                printf("Le fichier n'a pas pu être ouvert pour ecrire.\n");
               }


         break;
          }

         case 6:{
              afficher_liste_prof(lp);
               FILE *fp = fopen("Profils.txt", "r"); // Open the file in read mode
             if (fp != NULL) {
                 lire_profils_fichier(fp);
                 fclose(fp); // Close the file after reading
                  // Process the readForumList as needed
             } else {
                 printf("Le fichier n'a pas pu être ouvert pour lire.\n");
               }
           break;
          }

          case 7:{
           Auteur aut;
             aut=saisie_auteur(lp);
           la=ajouter_auteur(la,aut);
           FILE *fp = fopen("auteurs.txt", "a"); // Open the file in append mode
              if (fp != NULL) {
                ecrire_auteur_fichier(aut, fp);
                fclose(fp); // Close the file after writing
             } else {
                printf("Le fichier n'a pas pu être ouvert pour ecrire.\n");
               }

          break;
          }

         case 8:{
          afficher_liste_auteur(la);
            FILE *fp = fopen("auteurs.txt", "r"); // Open the file in read mode
             if (fp != NULL) {
                 lire_auteurs_fichier(fp);
                 fclose(fp); // Close the file after reading
                  // Process the readForumList as needed
             } else {
                 printf("Le fichier n'a pas pu être ouvert pour lire.\n");
               }
          break;
          }

          case 9:{
           Message msg;
           msg=saisie_message(&nb_messages,lm,lr,la);
           lm=ajouter_msg(lm,msg);
            FILE *fp = fopen("messages.txt", "a"); // Open the file in append mode
            if (fp != NULL) {
                ecrire_message_fichier(msg,fp);
                fclose(fp); // Close the file after writing
            } else {
                printf("Le fichier n'a pas pu être ouvert\n");
            }

          break;
          }

          case 10:{
          afficher_liste_msg(lm);
          // Read messages from the file and store them in a linked list
            FILE *fp = fopen("messages.txt", "r"); // Open the file in read mode
            if (fp!= NULL) {
                lire_messages_fichier (fp);
                fclose(fp); // Close the file after reading
                // Process the readMsgList as needed
            } else {
                printf("Le fichier n'a pas pu être ouvert\n");
            }
          break;
          }
         case 11:{

              Message m;
              int id;
              printf("donner id du message:\n");
              scanf("%d", &id);
              m = trouver_id(lm,id);
              liste_reponse(m, lm);

             break;
}
           case 12:{

              char theme[50];
              printf("donner theme du rubrique:\n");
              scanf("%s",theme);
              afficher_messages_rubrique(lm,lr,theme);
              break;}

              case 13:{
            struct tm date_verifier;
            printf("\t\t\t\tsaisir une date sous forme:-/-/- \n");
            scanf("%d/%d/%d",&date_verifier.tm_mday,&date_verifier.tm_mon,&date_verifier.tm_year);
              Afficher_messages_jour(date_verifier,lm);
              break;
              }
              case 14:{
                //le message
                int id;
                Message msg;
                printf("\t\t\t\t taper le ID du message:\n");
                scanf("%d",&id);
                msg=trouver_id(lm,id);

                char mot[10];
                printf("\t\t\t\tdonner le mot:\n");
                scanf("%s",mot);
                Rechercher_mot(msg,mot);
              break;
              }
              case 15:{
                 char theme[50];
                 printf("\t\t\t\tsaisir theme du rubrique:\n");
                scanf("%s",theme);
                if(trouver_rub(lr,theme)==1){
                 Afficher_messages_chrono(lm,lr,theme);}
                else{
                    printf("aucun rubrique:\n");
                }
              break;
              }
            case 16:{
             Retrouve_messages_auteur_profil(lm,la,lp);


            break;
            }
            case 17:{
                char theme[50];
                printf("saisir theme du rubrique:");
                scanf("%s",theme);
             Retrouver_profiles_par_rubrique(lm,lr,lp,theme);


            break;
            }
          case 18:{
           moyenneNombreMessagesMemeAuteur(la);
          break;
          }
          case 19:{
          compterMessagesParDate(lm);
          break;
          }
          case 20:{
           jourLePlusFrequente(lm);
          break;
          }
          case 21:{
           messagesParRubrique(lm,lr);
          break;
          }
           case 22:{
        longueurTexteMoyen(lm);
          break;
          }
          case 23:{
          supprimer(lf,lr,lp,la,lm);
          break;
          }
          case 24:{
          modifier(lf,lr,lp,la,lm);
          break;
          }
          case 25:{
          printf("Au revoir\n");
          break;
          }
          default:{
            printf("choix invalide. Veuillez choisir une option valide.\n");
        }
        }


    }while(choix !=25);

    free_liste_forum(lf);
    free_liste_rubrique(lr);
    free_liste_profil(lp);
    free_liste_auteur(la);
    free_liste_message(lm);

    return 0;
}




