/*      lemmatiseur.h
 *
 *  This file is part of COLLATINUS.
 *
 *  COLLATINUS is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  COLLATINVS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with COLLATINUS; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * © Yves Ouvrard, 2009 - 2016
 */

#ifndef LEMMATISEUR_H
#define LEMMATISEUR_H

#include <QMap>
#include <QString>
#include <QStringList>
#include <QtCore/QCoreApplication>

#include "irregs.h"
#include "lemme.h"
#include "modele.h"

class Irreg;
class Lemme;
class Radical;

typedef struct
{
    QString grq;
    QString morpho;
    QString sufq;
} SLem;

typedef QMap<Lemme*, QList<SLem> > MapLem;
#include "mot.h"

typedef QPair<QRegExp, QString> Reglep;

class Lemmat : public QObject
{
    Q_OBJECT

   private:
    QHash<QString,int> _hLem;
    QStringList _couleurs;
    // fonction d'initialisation
    void ajAssims();
    void ajContractions();
    int  aRomano(QString f);
    void lisIrreguliers();
    void lisFichierLexique(QString filepath);
    void lisLexique();
    void lisExtension();
    void lisModeles();
    void lisMorphos(QString lang);
    void lisNombres();
    void lisParPos();
    void lisTraductions(bool base, bool extension);
    // variables et utils
    QMap<QString, QString> assims;
    QMap<QString, QString> assimsq;
    QStringList cherchePieds(int nbr, QString ligne, int i, bool pentam);
    QMap<QString, QString> _contractions;
    QMultiMap<QString, Desinence *> _desinences;
    QString decontracte(QString d);
    QStringList formeq(QString forme, bool *nonTrouve, bool debPhr,
                       int accent = 0);
    bool inv(Lemme *l, const MapLem ml);
    QMultiMap<QString, Irreg *> _irregs;
    QString _cible;  // langue courante, 2 caractères
    QMap<QString, QString> _cibles;
    QMap<QString, Lemme *> _lemmes;
    QStringList             lignesFichier(QString nf);
    QMap<QString, Modele *> _modeles;
    QMap<QString,QStringList> _morphos;
    QMap<QString,QStringList> _cas;
    QMap<QString,QStringList> _genres;
    QMap<QString,QStringList> _nombres;
    QMap<QString,QStringList> _temps;
    QMap<QString,QStringList> _modes;
    QMap<QString,QStringList> _voix;
    QMap<QString,QStringList> _motsClefs;
    // Les morphos doivent pouvoir être données en anglais !
    QMultiMap<QString, Radical *> _radicaux;
    QList<Reglep> _reglesp;
    QMap<QString, QString> _variables;
    // options
    bool _alpha;
    bool _extension; // = false;
    bool _formeT;
    bool _html;
    bool _majPert;
    bool _morpho;
    bool _nonRec;
    QMap<QString,QString> _catLasla;
    void lisCat();

    QMap<QString, int> _tagOcc; // Nombre d'occurrences du tag.
    QMap<QString, int> _tagTot; // Nombre total en fonction du premier caractère du tag.
    QMap<QString, int> _trigram; // Nombre d'occurrences des séquences de 3 tags.
    void lisTags(bool tout = false);

    QString _resDir; // Le chemin du répertoire de ressources
    bool _extLoaded; // = true après chargement de l'extension
    // Lorsque j'ai chargé l'extension, je dois pouvoir ignorer les analyses qui en viennent.
    bool _nbrLoaded; // Si les nombres ont été chargés, je dois les effacer avant de les charger à nouveau.

   public:
    Lemmat(QObject *parent = 0, QString resDir="");
    void ajDesinence(Desinence *d);
    void ajModele(Modele *m);
    void ajRadicaux(Lemme *l);
    QString assim(QString a);
    QString assimq(QString a);
    QString cible();
    QMap<QString, QString> cibles();
    QString desassim(QString a);
    QString desassimq(QString a);
    static QString deramise(QString r);
    static bool estRomain(QString f);
    QStringList frequences(QString txt);
    MapLem lemmatise(QString f);  // lemmatise une forme
    QString lemmatiseFichier(QString f, bool alpha = false,
                             bool cumVocibus = false, bool cumMorpho = false,
                             bool nreconnu = true);
    QStringList lemmatiseF(QString f, bool deb);
    // lemmatiseM lemmatise une forme en contexte
    //MapLem lemmatiseM(QString f, bool debPhr = true);
    MapLem lemmatiseM(QString f, bool debPhr = true, bool desas  =false);
    // lemmatiseT lemmatise un texte
    QString lemmatiseT(QString &t);
    QString lemmatiseT(QString &t, bool alpha, bool cumVocibus = false,
                       bool cumMorpho = false, bool nreconnu = false);
    Lemme *lemme(QString l);
    // lemmes(ml) renvoie la liste des graphies des lemmes
    QStringList lemmes(MapLem ml);
    Modele *modele(QString m);
    QString morpho(int i);
    QString parPos(QString f);
    QString scandeTxt(QString texte, int accent = 0, bool stats = false);
    // QStringList           suffixes;
    QMap<QString, QString> suffixes;
    QString variable(QString v);
    // Lire un fichier de césures étymologiques (non-phonétiques)
    void lireHyphen (QString fichierHyphen);

    // accesseurs d'options
    bool optAlpha();
    bool optHtml();
    bool optFormeT();
    bool optMajPert();
    bool optMorpho();
    bool optExtension();

    // Pour l'internationalisation
    QString cas(int i);
    QString genre(int i);
    QString nombre(int i);
    QString temps(int i);
    QString modes(int i);
    QString voix(int i);
    QString motsClefs(int i);

    // Pour le tagger
    QString tagTexte(QString t, int p, bool affTout = true);
//    QString tagPhrase(QString phr);
    QString tag(Lemme *l, QString morph);
    int fraction(QString listTags);
    int tagOcc(QString t);

    // Code en 9 pour le LASLA
    QString k9(QString m);

    void verbaOut(QString fichier); // Connaître l'usage des mots connus
    void verbaCognita(QString fichier, bool vb=false); // Coloriser le texte avec les mots connus

   public slots:
    // modificateurs d'options
    void setAlpha(bool a);
    void setCible(QString c);
    void setHtml(bool h);
    void setFormeT(bool f);
    void setMajPert(bool mp);
    void setMorpho(bool m);
    void setNonRec(bool n);
    void setExtension(bool e);
};

#endif
