#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>

struct proje
{
    char aciklama[100];
    char version[50];
    char alanlar[50];
    char nokta_sayisi[50];
    char data[50];
};

struct koordinat
{
    float x,y,z;
};
struct renk
{
    int r,g,b;
};
struct xyz_rgb2{
   float x,y,z;
   int r,g,b;

};


int main()
{
    FILE *dosya,*cikti;
    cikti = fopen("cikti.txt","w");
    DIR *klasor;
    klasor = opendir(".");
    struct dirent *coklu_dosya;
    char dosya_adlari[20][20];
    int dosya_sayisi=0;
    int d_sayi;
    int kure_sayaci=0;


    while((coklu_dosya=readdir(klasor))!=NULL)
    {
        strcpy(dosya_adlari[dosya_sayisi],coklu_dosya->d_name);
        printf("%s\n",dosya_adlari[dosya_sayisi]);


        dosya_sayisi++;
    }

    printf("DOSYA ISIMLERI: \n\n");
    for(d_sayi=0 ; d_sayi<dosya_sayisi ; d_sayi++)
    {
        char output_dosyasi[6] = "cikti";
        cikti=fopen((strcat(output_dosyasi,dosya_adlari[d_sayi])),"a");

        if(strstr(dosya_adlari[d_sayi],".nkt"))
        {
            printf("%s \n",dosya_adlari[d_sayi]);
            dosya=fopen(dosya_adlari[d_sayi],"r");
        }
       else
       {
           printf("%s dosyasinin uzantisi .nkt turunde degil.\n",dosya_adlari[d_sayi]);
           continue;

       }

       printf("\n-------------------------\n");

       struct proje p;
       int i=0;//binary de satir sayisini tutar.
       char points[50];
       char s1[20]; // p.noktasayisinin stringi
       char s2[20]; //p.alanlarin stringini tutar
       int sayi,m,j;
       char s3[20];// data ascii cumlesi datanin s si
       char s4[20]; // ascii nin s si
       int satir_sayisi=0;
       int kontrol;
       int yindis1,yindis2;
       int uindis1,uindis2;
       float toplam=0.0;
       float ortalama=0.0;
       float en_yakin_mesafe;
       float en_uzak_mesafe;
       float kure_uzaklik;
       float kure_x,kure_y,kure_z,yaricap;
       float en_kucuk_x,en_kucuk_y,en_kucuk_z;
       float en_buyuk_x,en_buyuk_y,en_buyuk_z;
       int kucuk_indis,buyuk_indis;
       float uzaklik=0.0;
       int secim;
       int satir=0;
       double kenar_uzunlugu;
       int str_version[20];
       int sayi2; // verion nun sayisini tutar
       char *kelime;
       char *ayrac=" ";
       int k_sayisi=0;

       printf("BASLIK BILGILERI: \n\n");

       fgets(p.aciklama,100,dosya);
       printf("%s",p.aciklama);
       fgets(p.version,50,dosya);
       printf("%s",p.version);
       fgets(p.alanlar,50,dosya);
       printf("%s",p.alanlar);
       fgets(p.nokta_sayisi,50,dosya);
       printf("%s",p.nokta_sayisi);
       fgets(p.data,50,dosya);
       printf("%s",p.data);
       sscanf(p.nokta_sayisi,"%s %d",s1,&sayi);
       sscanf(p.data,"%s %s",s3,s4);
       sscanf(p.version,"%s %d",str_version,&sayi2);

       int ftellk=ftell(dosya);
       struct koordinat renkli_n[sayi];
       struct renk renkli[sayi];
       struct koordinat renksiz_n[sayi];
       struct xyz_rgb2 rgbli[sayi];

       if(sayi2!=1)
       {
           printf("Version bilgisi hatalidir.\n");

       }
       else
       {




       if(strstr(p.alanlar,"ALANLAR x y z r g b"))
       {
            kontrol = 1;
       }
       else if(strstr(p.alanlar,"ALANLAR x y z"))
       {
            kontrol = 0;
       }
       else
       {
            kontrol = -1;
       }


       printf("\n\n");
       fprintf(cikti,"\n\n");
       if(strstr(s4,"ascii") || strstr(s4,"ASCII"))
       {
            printf("Bu dosya ascii formatindadir.\n");
            fprintf(cikti,"Bu dosya ascii formatindadir.\n");

        while(fgets(points,50,dosya) != NULL)
        {
            if(kontrol == 1)
            {

                sscanf(points,"%f %f %f %d %d %d",&renkli_n[satir_sayisi].x,&renkli_n[satir_sayisi].y,&renkli_n[satir_sayisi].z,&renkli[satir_sayisi].r,&renkli[satir_sayisi].g,&renkli[satir_sayisi].b);
                //printf(" \t %f \t%f \t%f \t%d \t%d \t%d\n ",renkli_n[satir_sayisi].x,renkli_n[satir_sayisi].y,renkli_n[satir_sayisi].z,renkli[satir_sayisi].r,renkli[satir_sayisi].g,renkli[satir_sayisi].b);


                 satir_sayisi++;
            }
            else if (kontrol == 0)
            {

                sscanf(points,"%f %f %f ",&renksiz_n[satir_sayisi].x,&renksiz_n[satir_sayisi].y,&renksiz_n[satir_sayisi].z);
                //printf(" \t %f \t %f \t %f \n",renksiz_n[satir_sayisi].x,renksiz_n[satir_sayisi].y,renksiz_n[satir_sayisi].z);
                satir_sayisi++;
            }
        }



        while(1)
        {
            printf("1:DOSYA KONTROLU\n");
            printf("2:DOSYA EN YAKIN EN UZAK NOKTALAR\n");
            printf("3:KUP OLUSTURMA\n");
            printf("4:KURE OLUSTURMA\n");
            printf("5:NOKTALARIN BIRBIRLERINE OLAN UZAKLIKLARI\n\n");
            printf("Seciminiz nedir: ");
            scanf("%d",&secim);
            printf("\n");
            fprintf(cikti,"\n");

            if(secim == 1)
            {
                printf("DOSYA KONTROLU:\n\n");
                fprintf(cikti,"DOSYA KONTROLU: \n\n");

                if(kontrol == 1)
                {
                    printf("Dosya renk bilgisi icerir.\n");
                    fprintf(cikti,"Dosya renk bilgisi icerir.\n");
                }
                else if(kontrol==0)
                {
                    printf("Dosya renk bilgisi icermez.\n");
                    fprintf(cikti,"Dosya renk bilgisi icermez.\n");
                }
                else if(kontrol==-1)
                {
                    printf("Basliktaki alan bilgileri hatalidir.\n");
                    fprintf(cikti,"Basliktaki alan bilgileri hatalidir.\n");
                    printf("Dosyadan cikiliyor.\n");
                    break;
                }

                if(kontrol == 1)
                {

                for(satir=0 ; satir<sayi ; satir++)
                {


                    if(renkli[satir].r>255 || renkli[satir].r<0)
                    {
                        printf("%d. Satirdaki r bilgisi 0 - 255 arasinda degildir.\n",satir+1);
                        fprintf(cikti,"%d. Satirdaki r bilgisi 0 - 255 arasinda degildir.\n",satir+1);
                    }
                    else if(renkli[satir].g>255 || renkli[satir].g<0)
                    {
                        printf("%d. Satirdaki g bilgisi 0 - 255 arasinda degildir.\n",satir+1);
                        fprintf(cikti,"%d. Satirdaki g bilgisi 0 - 255 arasinda degildir.\n",satir+1);
                    }
                    else if(renkli[satir].b>255 || renkli[satir].b<0)
                    {
                        printf("%d. Satirdaki b bilgisi 0 - 255 arasinda degildir.\n",satir+1);
                        fprintf(cikti,"%d. Satirdaki b bilgisi 0 - 255 arasinda degildir.\n",satir+1);
                    }
                }


                }

                if(sayi==satir_sayisi)
                {
                    printf("Basliktaki ve dosyadaki nokta sayisi uyumludur.\n");
                    fprintf(cikti,"Basliktaki ve dosyadaki nokta sayisi uyumludur.\n");
                    printf("Dosyadaki nokta sayisi:%d\n",satir_sayisi);
                    fprintf(cikti,"Dosyadaki nokta sayisi:%d\n",satir_sayisi);
                }
                else
                {
                    printf("Basliktaki ve dosyadaki nokta sayisi uyumlu degildir.\n");
                    fprintf(cikti,"Basliktaki ve dosyadaki nokta sayisi uyumlu degildir.\n");
                    printf("Dosyadan cikiliyor...\n");
                    break;
                }
            }
            printf("\n");
            fprintf(cikti,"\n");

            if(secim == 2)
            {
                printf("DOSYADAKI EN YAKIN VE EN UZAK NOKTALAR:\n\n");
                fprintf(cikti,"DOSYADAKI EN YAKIN VE EN UZAK NOKTALAR:\n\n");
                if (kontrol == 1)
                {
                    en_yakin_mesafe=sqrt(pow((renkli_n[0].x-renkli_n[1].x),2) + pow((renkli_n[0].y-renkli_n[1].y),2) + pow((renkli_n[0].z-renkli_n[1].z),2));
                    for(j=0; j<sayi; j++)
                    {
                        for(m=j+1; m<sayi; m++)
                        {
                            if(sqrt(pow((renkli_n[j].x-renkli_n[m].x),2) + pow((renkli_n[j].y-renkli_n[m].y),2) + pow((renkli_n[j].z-renkli_n[m].z),2))<en_yakin_mesafe)
                            {
                                en_yakin_mesafe=sqrt(pow((renkli_n[j].x-renkli_n[m].x),2) + pow((renkli_n[j].y-renkli_n[m].y),2) + pow((renkli_n[j].z-renkli_n[m].z),2));
                                yindis1=j;
                                yindis2=m;
                            }

                        }

                    }

                    printf("En yakin mesafe=%f \n\n",en_yakin_mesafe);
                    fprintf(cikti,"En yakin mesafe=%f \n\n",en_yakin_mesafe);
                    printf("Yakin nokta bilgileri:\n");
                    fprintf(cikti,"Yakin nokta bilgileri:\n");
                    printf(" 1.NOKTA : %f %f %f %d %d %d\n",renkli_n[yindis1].x,renkli_n[yindis1].y,renkli_n[yindis1].z,renkli[yindis1].r,renkli[yindis1].g,renkli[yindis1].b);
                    fprintf(cikti," 1.NOKTA : %f %f %f %d %d %d\n",renkli_n[yindis1].x,renkli_n[yindis1].y,renkli_n[yindis1].z,renkli[yindis1].r,renkli[yindis1].g,renkli[yindis1].b);
                    printf(" 2.NOKTA : %f %f %f %d %d %d\n",renkli_n[yindis2].x,renkli_n[yindis2].y,renkli_n[yindis2].z,renkli[yindis2].r,renkli[yindis2].g,renkli[yindis2].b);
                    fprintf(cikti," 2.NOKTA : %f %f %f %d %d %d\n",renkli_n[yindis2].x,renkli_n[yindis2].y,renkli_n[yindis2].z,renkli[yindis2].r,renkli[yindis2].g,renkli[yindis2].b);

                    en_uzak_mesafe=sqrt(pow((renkli_n[0].x-renkli_n[1].x),2) + pow((renkli_n[0].y-renkli_n[1].y),2) + pow((renkli_n[0].z-renkli_n[1].z),2));
                    for(j=0; j<sayi; j++)
                    {
                        for(m=j+1; m<sayi; m++)
                        {
                            if(sqrt(pow((renkli_n[j].x-renkli_n[m].x),2) + pow((renkli_n[j].y-renkli_n[m].y),2) + pow((renkli_n[j].z-renkli_n[m].z),2))>en_uzak_mesafe)
                            {
                                en_uzak_mesafe=sqrt(pow((renkli_n[j].x-renkli_n[m].x),2) + pow((renkli_n[j].y-renkli_n[m].y),2) + pow((renkli_n[j].z-renkli_n[m].z),2));
                                uindis1=j;
                                uindis2=m;
                            }

                        }

                    }

                    printf("En uzak mesafe:%f \n\n",en_uzak_mesafe);
                    fprintf(cikti,"En uzak mesafe:%f \n\n",en_uzak_mesafe);
                    printf("Uzak nokta bilgileri:\n");
                    fprintf(cikti,"Uzak nokta bilgileri:\n");
                    printf(" 1.NOKTA : %f %f %f %d %d %d\n",renkli_n[uindis1].x,renkli_n[uindis1].y,renkli_n[uindis1].z,renkli[uindis1].r,renkli[uindis1].g,renkli[uindis1].b);
                    fprintf(cikti," 1.NOKTA : %f %f %f %d %d %d\n",renkli_n[uindis1].x,renkli_n[uindis1].y,renkli_n[uindis1].z,renkli[uindis1].r,renkli[uindis1].g,renkli[uindis1].b);
                    printf(" 2.NOKTA : %f %f %f %d %d %d\n",renkli_n[uindis2].x,renkli_n[uindis2].y,renkli_n[uindis2].z,renkli[uindis2].r,renkli[uindis2].g,renkli[uindis2].b);
                    fprintf(cikti," 2.NOKTA : %f %f %f %d %d %d\n",renkli_n[uindis2].x,renkli_n[uindis2].y,renkli_n[uindis2].z,renkli[uindis2].r,renkli[uindis2].g,renkli[uindis2].b);


                }
                else if(kontrol == 0)
                {
                    en_yakin_mesafe=sqrt(pow((renksiz_n[0].x-renksiz_n[1].x),2) + pow((renksiz_n[0].y-renksiz_n[1].y),2) + pow((renksiz_n[0].z-renksiz_n[1].z),2));
                    for(j=0; j<sayi; j++)
                    {
                        for(m=j+1; m<sayi; m++)
                        {
                            if(sqrt(pow((renksiz_n[j].x-renksiz_n[m].x),2) + pow((renksiz_n[j].y-renksiz_n[m].y),2) + pow((renksiz_n[j].z-renksiz_n[m].z),2))<en_yakin_mesafe)
                            {
                                en_yakin_mesafe=sqrt(pow((renksiz_n[j].x-renksiz_n[m].x),2) + pow((renksiz_n[j].y-renksiz_n[m].y),2) + pow((renksiz_n[j].z-renksiz_n[m].z),2));
                                yindis1=j;
                                yindis2=m;
                            }

                        }

                    }

                    printf("En yakin mesafe=%f \n\n",en_yakin_mesafe);
                    fprintf(cikti,"En yakin mesafe=%f \n\n",en_yakin_mesafe);
                    printf("Yakin nokta bilgileri:\n");
                    fprintf(cikti,"Yakin nokta bilgileri:\n");
                    printf(" 1.NOKTA : %f %f %f\n",renksiz_n[yindis1].x,renksiz_n[yindis1].y,renksiz_n[yindis1].z);
                    fprintf(cikti," 1.NOKTA : %f %f %f\n",renksiz_n[yindis1].x,renksiz_n[yindis1].y,renksiz_n[yindis1].z);
                    printf(" 2.NOKTA : %f %f %f\n",renksiz_n[yindis2].x,renksiz_n[yindis2].y,renksiz_n[yindis2].z);
                    fprintf(cikti," 2.NOKTA : %f %f %f\n",renksiz_n[yindis2].x,renksiz_n[yindis2].y,renksiz_n[yindis2].z);


                    en_uzak_mesafe=sqrt(pow((renksiz_n[0].x-renksiz_n[1].x),2) + pow((renksiz_n[0].y-renksiz_n[1].y),2) + pow((renksiz_n[0].z-renksiz_n[1].z),2));
                    for(j=0; j<sayi; j++)
                    {
                        for(m=j+1; m<sayi; m++)
                        {


                            if(sqrt(pow((renksiz_n[j].x-renksiz_n[m].x),2) + pow((renksiz_n[j].y-renksiz_n[m].y),2) + pow((renksiz_n[j].z-renksiz_n[m].z),2))>en_uzak_mesafe)
                            {
                                en_uzak_mesafe=sqrt(pow((renksiz_n[j].x-renksiz_n[m].x),2) + pow((renksiz_n[j].y-renksiz_n[m].y),2) + pow((renksiz_n[j].z-renksiz_n[m].z),2));
                                uindis1=j;
                                uindis2=m;
                            }

                        }

                    }

                    printf("En uzak mesafe:%f \n",en_uzak_mesafe);
                    fprintf(cikti,"En uzak mesafe:%f \n",en_uzak_mesafe);
                    printf("Uzak nokta bilgileri:\n");
                    fprintf(cikti,"Uzak nokta bilgileri:\n");
                    printf(" 1.NOKTA : %f %f %f\n",renksiz_n[uindis1].x,renksiz_n[uindis1].y,renksiz_n[uindis1].z);
                    fprintf(cikti," 1.NOKTA : %f %f %f\n",renksiz_n[uindis1].x,renksiz_n[uindis1].y,renksiz_n[uindis1].z);
                    printf(" 2.NOKTA : %f %f %f\n",renksiz_n[uindis2].x,renksiz_n[uindis2].y,renksiz_n[uindis2].z);
                    fprintf(cikti," 2.NOKTA : %f %f %f\n",renksiz_n[uindis2].x,renksiz_n[uindis2].y,renksiz_n[uindis2].z);


                }
            }
            printf("\n");
            fprintf(cikti,"\n");
            if(secim == 3)
            {
                printf("KUP OLUSTURMA: \n\n");
                fprintf(cikti,"KUP OLUSTURMA: \n\n");
                if(kontrol == 1)
                {
                    en_kucuk_x=renkli_n[0].x;
                    en_kucuk_y=renkli_n[0].y;
                    en_kucuk_z=renkli_n[0].z;

                    for(j=0; j<sayi; j++)
                    {
                        if(renkli_n[j].x<en_kucuk_x)
                        {
                            en_kucuk_x=renkli_n[j].x;
                        }
                        if(renkli_n[j].y<en_kucuk_y)
                        {
                            en_kucuk_y=renkli_n[j].y;
                        }
                        if(renkli_n[j].z<en_kucuk_z)
                        {
                            en_kucuk_z=renkli_n[j].z;
                        }
                    }
                    printf("En kucuk x:%f\n",en_kucuk_x);
                    fprintf(cikti,"En kucuk x:%f\n",en_kucuk_x);
                    printf("En kucuk y:%f\n",en_kucuk_y);
                    fprintf(cikti,"En kucuk y:%f\n",en_kucuk_y);
                    printf("En kucuk z:%f\n",en_kucuk_z);
                    fprintf(cikti,"En kucuk z:%f\n",en_kucuk_z);
                    printf("\n");
                    fprintf(cikti,"\n");

                    en_buyuk_x=renkli_n[0].x;
                    en_buyuk_y=renkli_n[0].y;
                    en_buyuk_z=renkli_n[0].z;
                    for(j=0; j<sayi; j++)
                    {
                        if(renkli_n[j].x>en_buyuk_x)
                        {
                            en_buyuk_x=renkli_n[j].x;

                        }
                        if(renkli_n[j].y>en_buyuk_y)
                        {
                            en_buyuk_y=renkli_n[j].y;
                        }
                        if(renkli_n[j].z>en_buyuk_z)
                        {
                            en_buyuk_z=renkli_n[j].z;
                        }
                    }
                    printf("En buyuk x:%f\n",en_buyuk_x);
                    fprintf(cikti,"En buyuk x:%f\n",en_buyuk_x);
                    printf("En buyuk y:%f\n",en_buyuk_y);
                    fprintf(cikti,"En buyuk y:%f\n",en_buyuk_y);
                    printf("En buyuk z:%f\n",en_buyuk_z);
                    fprintf(cikti,"En buyuk z:%f\n",en_buyuk_z);
                    printf("\n");
                    fprintf(cikti,"\n");

                    if(en_buyuk_x>en_buyuk_y && en_buyuk_x>en_buyuk_z)
                    {
                        en_buyuk_y=en_buyuk_x;
                        en_buyuk_z=en_buyuk_x;
                    }
                    if(en_buyuk_y>en_buyuk_x && en_buyuk_y>en_buyuk_z)
                    {
                        en_buyuk_x=en_buyuk_y;
                        en_buyuk_z=en_buyuk_y;
                    }
                    if(en_buyuk_z>en_buyuk_x && en_buyuk_z>en_buyuk_y)
                    {
                        en_buyuk_x=en_buyuk_z;
                        en_buyuk_y=en_buyuk_z;
                    }
                    if(en_kucuk_x<en_kucuk_y && en_kucuk_x<en_kucuk_z)
                    {
                        en_kucuk_y=en_kucuk_x;
                        en_kucuk_z=en_kucuk_x;
                    }
                    if(en_kucuk_y<en_kucuk_x && en_kucuk_y<en_kucuk_z)
                    {
                        en_kucuk_x=en_kucuk_y;
                        en_kucuk_z=en_kucuk_y;
                    }
                    if(en_kucuk_z<en_kucuk_x && en_kucuk_z<en_kucuk_y)
                    {
                        en_kucuk_x=en_kucuk_z;
                        en_kucuk_y=en_kucuk_z;
                    }

                    kenar_uzunlugu = en_buyuk_x-en_kucuk_x;

                    printf("Bir kenarinin uzunlugu: %f\n\n",kenar_uzunlugu);
                    fprintf(cikti,"Bir kenarinin uzunlugu: %f\n",kenar_uzunlugu);

                    printf("1. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_kucuk_z);
                    fprintf(cikti,"1. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_kucuk_z);
                    printf("2. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_kucuk_z);
                    fprintf(cikti,"2. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_kucuk_z);
                    printf("3. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_kucuk_z);
                    fprintf(cikti,"3. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_kucuk_z);
                    printf("4. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_buyuk_z);
                    fprintf(cikti,"4. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_buyuk_z);
                    printf("5. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_kucuk_z);
                    fprintf(cikti,"5. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_kucuk_z);
                    printf("6. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_buyuk_z);
                    fprintf(cikti,"6. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_buyuk_z);
                    printf("7. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_buyuk_z);
                    fprintf(cikti,"7. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_buyuk_z);
                    printf("8. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_buyuk_z);
                    fprintf(cikti,"8. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_buyuk_z);
                }
                else if(kontrol == 0)
                {
                    en_kucuk_x=renksiz_n[0].x;
                    en_kucuk_y=renksiz_n[0].y;
                    en_kucuk_z=renksiz_n[0].z;

                    for(j=0; j<sayi; j++)
                    {
                        if(renksiz_n[j].x<en_kucuk_x)
                        {
                            en_kucuk_x=renksiz_n[j].x;
                        }
                         if(renksiz_n[j].y<en_kucuk_y)
                        {
                            en_kucuk_y=renksiz_n[j].y;
                        }
                         if(renksiz_n[j].z<en_kucuk_z)
                        {
                            en_kucuk_z=renksiz_n[j].z;
                        }
                    }
                    printf("En kucuk x:%f\n",en_kucuk_x);
                    fprintf(cikti,"En kucuk x:%f\n",en_kucuk_x);
                    printf("En kucuk y:%f\n",en_kucuk_y);
                    fprintf(cikti,"En kucuk y:%f\n",en_kucuk_y);
                    printf("En kucuk z:%f\n",en_kucuk_z);
                    fprintf(cikti,"En kucuk z:%f\n",en_kucuk_z);
                    printf("\n");
                    fprintf(cikti,"\n");
                    en_buyuk_x=renksiz_n[0].x;
                    en_buyuk_y=renksiz_n[0].y;
                    en_buyuk_z=renksiz_n[0].z;

                    for(j=0; j<sayi; j++)
                    {
                        if(renksiz_n[j].x>en_buyuk_x)
                        {
                            en_buyuk_x=renksiz_n[j].x;
                        }
                        if(renksiz_n[j].y>en_buyuk_y)
                        {
                            en_buyuk_y=renksiz_n[j].y;
                        }
                         if(renksiz_n[j].z>en_buyuk_z)
                        {
                            en_buyuk_z=renksiz_n[j].z;
                        }
                    }
                    printf("En buyuk x:%f\n",en_buyuk_x);
                    fprintf(cikti,"En buyuk x:%f\n",en_buyuk_x);
                    printf("En buyuk y:%f\n",en_buyuk_y);
                    fprintf(cikti,"En buyuk y:%f\n",en_buyuk_y);
                    printf("En buyuk z:%f\n",en_buyuk_z);
                    fprintf(cikti,"En buyuk z:%f\n",en_buyuk_z);
                    printf("\n");
                    fprintf(cikti,"\n");
                    if(en_buyuk_x>en_buyuk_y && en_buyuk_x>en_buyuk_z)
                    {
                        en_buyuk_y=en_buyuk_x;
                        en_buyuk_z=en_buyuk_x;
                    }
                    else if(en_buyuk_y>en_buyuk_x && en_buyuk_y>en_buyuk_z)
                    {
                        en_buyuk_x=en_buyuk_y;
                        en_buyuk_z=en_buyuk_y;
                    }
                    else if(en_buyuk_z>en_buyuk_x && en_buyuk_z>en_buyuk_y)
                    {
                        en_buyuk_x=en_buyuk_z;
                        en_buyuk_y=en_buyuk_z;
                    }
                    else if(en_kucuk_x<en_kucuk_y && en_kucuk_x<en_kucuk_z)
                    {
                        en_kucuk_y=en_kucuk_x;
                        en_kucuk_z=en_kucuk_x;
                    }
                    else if(en_kucuk_y<en_kucuk_x && en_kucuk_y<en_kucuk_z)
                    {
                        en_kucuk_x=en_kucuk_y;
                        en_kucuk_z=en_kucuk_y;
                    }
                    else if(en_kucuk_z<en_kucuk_x && en_kucuk_z<en_kucuk_y)
                    {
                        en_kucuk_x=en_kucuk_z;
                        en_kucuk_y=en_kucuk_z;
                    }

                    kenar_uzunlugu = en_buyuk_x-en_kucuk_x;

                    printf("Bir kenarinin uzunlugu: %f\n\n",kenar_uzunlugu);
                    fprintf(cikti,"Bir kenarinin uzunlugu: %f\n\n",kenar_uzunlugu);

                    printf("1. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_kucuk_z);
                    fprintf(cikti,"1. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_kucuk_z);
                    printf("2. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_kucuk_z);
                    fprintf(cikti,"2. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_kucuk_z);
                    printf("3. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_kucuk_z);
                    fprintf(cikti,"3. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_kucuk_z);
                    printf("4. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_buyuk_z);
                    fprintf(cikti,"4. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_buyuk_z);
                    printf("5. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_kucuk_z);
                    fprintf(cikti,"5. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_kucuk_z);
                    printf("6. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_buyuk_z);
                    fprintf(cikti,"6. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_buyuk_z);
                    printf("7. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_buyuk_z);
                    fprintf(cikti,"7. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_buyuk_z);
                    printf("8. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_buyuk_z);
                    fprintf(cikti,"8. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_buyuk_z);

                }
            }

            printf("\n");
            fprintf(cikti,"\n");
            if(secim == 4)
            {
                printf("KURE OLUSTURMA: \n\n");
                fprintf(cikti,"KURE OLUSTURMA: \n\n");

                printf("\n");
                if(kure_sayaci==0){
                printf("Kurenin merkez x y z bilgilerinin giriniz:\n");
                scanf("%f %f %f",&kure_x,&kure_y,&kure_z);
                printf("Kurenin yaricapini giriniz:");
                scanf("%f",&yaricap);
                kure_sayaci++;
                }

                fprintf(cikti,"Merkez x y z : %f %f %f\nYaricap: %f\n\n",kure_x,kure_y,kure_z,yaricap);

                if(kontrol == 1)
                {

                    printf("Verilen koordinatlarin icinde kalan noktalar:\n");
                    fprintf(cikti,"Verilen koordinatlarin icinde kalan noktalar:\n");

                    for(j=0 ; j<sayi ; j++)
                    {
                        kure_uzaklik = sqrt(pow((kure_x-renkli_n[j].x),2) + pow((kure_y-renkli_n[j].y),2) + pow((kure_z-renkli_n[j].z),2));

                        if(kure_uzaklik<yaricap)
                        {

                            printf("%f %f %f\n",renkli_n[j].x,renkli_n[j].y,renkli_n[j].z);
                            fprintf(cikti,"%f %f %f\n",renkli_n[j].x,renkli_n[j].y,renkli_n[j].z);

                        }
                    }
                }
                else if(kontrol == 0)
                {
                    printf("Verilen koordinatlarin icinde kalan noktalar:\n");
                    fprintf(cikti,"Verilen koordinatlarin icinde kalan noktalar:\n");
                    for(j=0 ; j<sayi ; j++)
                    {
                        kure_uzaklik = sqrt(pow((kure_x-renksiz_n[j].x),2) + pow((kure_y-renksiz_n[j].y),2) + pow((kure_z-renksiz_n[j].z),2));

                        if(kure_uzaklik<yaricap)
                        {

                            printf("%f %f %f\n",renksiz_n[j].x,renksiz_n[j].y,renksiz_n[j].z);
                            fprintf(cikti,"%f %f %f\n",renksiz_n[j].x,renksiz_n[j].y,renksiz_n[j].z);

                        }
                    }

                }

            }
            printf("\n");
            fprintf(cikti,"\n");
            if(secim == 5)
            {
                printf("NOKTALARIN BIRBIRINE OLAN UZAKLIKLARININ ORTALAMASI: \n\n");
                fprintf(cikti,"NOKTALARIN BIRBIRINE OLAN UZAKLIKLARININ ORTALAMASI: \n\n");
                if(kontrol == 1)
                {
                    for(j=0; j<sayi; j++)
                    {

                        for(m=j+1; m<sayi; m++)
                        {
                            uzaklik = sqrt(pow((renkli_n[j].x-renkli_n[m].x),2) + pow((renkli_n[j].y-renkli_n[m].y),2) + pow((renkli_n[j].z-renkli_n[m].z),2));
                            toplam = uzaklik + toplam ;

                        }


                    }
                      ortalama = toplam/(sayi*(sayi-1)/2);


    printf("Ortalama: %f\n",ortalama);
    fprintf(cikti,"Ortalama: %f\n",ortalama);


                }
                else if(kontrol == 0)
                {
            for(j=0;j<sayi;j++)
        {
        for(m=j+1;m<sayi;m++)
        {
            uzaklik = sqrt(pow((renksiz_n[j].x-renksiz_n[m].x),2) + pow((renksiz_n[j].y-renksiz_n[m].y),2) + pow((renksiz_n[j].z-renksiz_n[m].z),2));
            toplam = uzaklik + toplam ;
        }
    }
    ortalama = toplam/((sayi*(sayi-1)/2));

    printf("Ortalama: %f\n",ortalama);
    fprintf(cikti,"Ortalama: %f\n",ortalama);


                }
            }

if(secim==6)
{
    break;
}

//while(1) in
        }

        //ascii
    }

    else if(strstr(s4,"binary") || strstr(s4,"BINARY"))
    {

    printf("Dosya binary formatindadir.\n");
    fprintf(cikti,"Dosya binary formatindadir.\n");
    FILE *dosya=fopen(dosya_adlari[d_sayi],"rb");

    if(kontrol == 1)
    {

       fseek(dosya,ftellk+2L,SEEK_SET);
       /* rewind(dosya); */
        for(i=0 ; i<sayi ; i++)
        {
            fread(&rgbli[i],sizeof(struct xyz_rgb2),1,dosya);
            printf("%f %f %f %d %d %d\n",rgbli[i].x,rgbli[i].y,rgbli[i].z,rgbli[i].r,rgbli[i].g,rgbli[i].b);
        }

    }
    else if( kontrol == 0)
    {



        fseek(dosya,ftellk,SEEK_SET);
        for(i=0;i<sayi;i++)
        {
            fread(&renksiz_n,sizeof(renksiz_n),1,dosya);
            printf("%f %f %f\n",renksiz_n[i].x,renksiz_n[i].y,renksiz_n[i].z);

        }



    }
         while(1)
         {
            printf("1:DOSYA KONTROLU\n");
            printf("2:DOSYA EN YAKIN EN UZAK NOKTALAR\n");
            printf("3:KUP OLUSTURMA\n");
            printf("4:KURE OLUSTURMA\n");
            printf("5:NOKTALARIN BIRBIRLERINE OLAN UZAKLIKLARI\n");
            printf("Seciminiz nedir: ");
            scanf("%d",&secim);
            printf("\n");
            fprintf(cikti,"\n");
            if(secim == 1)
            {
                 if(kontrol == 1)
                {
                    printf("Dosya renk bilgisi iceirir.\n");
                    fprintf(cikti,"Dosya renk bilgisi icerir.\n");
                }
                else if(kontrol==0)
                {
                    printf("Dosya renk bilgisi icermez.\n");
                    fprintf(cikti,"Dosya renk bilgisi icermez.\n");
                }
                else if(kontrol==-1)
                {
                    printf("Basliktaki alan bilgileri hatalidir.\n");
                    fprintf(cikti,"Basliktaki alan bilgileri hatalidir.\n");
                    printf("Dosyadan cikiliyor.\n");
                    fprintf(cikti,"Dosyadan cikiliyor.\n");
                    exit(1);
                }

                if(kontrol == 1)
                {

                for(satir=0 ; satir<sayi ; satir++)
                {
                     if(rgbli[satir].r>255 || rgbli[satir].r<0)
                    {
                        printf("%d. Satirdaki r bilgisi 0 - 255 arasinda degildir.\n",satir+1);
                        fprintf(cikti,"%d. Satirdaki r bilgisi 0 - 255 arasinda degildir.\n");
                    }
                    else if(rgbli[satir].g>255 || rgbli[satir].g<0)
                    {
                        printf("%d. Satirdaki g bilgisi 0 - 255 arasinda degildir.\n",satir+1);
                        fprintf(cikti,"%d. Satirdaki g bilgisi 0 - 255 arasinda degildir.\n");
                    }
                    else if(rgbli[satir].b>255 || rgbli[satir].b<0)
                    {
                        printf("%d. Satirdaki b bilgisi 0 - 255 arasinda degildir.\n",satir+1);
                        fprintf(cikti,"%d. Satirdaki g bilgisi 0 - 255 arasinda degildir.\n");
                    }

                }

                }

                 if(sayi==i) // fread tum dosyayý bastan okudugu icin ilk satirlari almaddýk!!!
                {
                    printf("Basliktaki ve dosyadaki nokta sayisi uyumludur.\n");
                    fprintf(cikti,"Basliktaki ve dosyadaki nokta sayisi uyumludur.\n");
                    printf("Dosyadaki nokta sayisi:%d\n",i);
                }
                else
                {
                    printf("Basliktaki ve dosyadaki nokta sayisi uyumlu degildir.\n");
                    fprintf(cikti,"Basliktaki ve dosyadaki nokta sayisi uyumlu degildir.\n");
                    printf("Dosyadan cikiliyor...\n");
                    fprintf(cikti,"Dosyadan cikiliyor...\n");
                    exit(1);
                }

            }
            printf("\n");
            fprintf(cikti,"\n");
            if(secim == 2)
            {
                if(kontrol == 1)
                {
                    en_yakin_mesafe=sqrt(pow((rgbli[0].x-rgbli[1].x),2) + pow((rgbli[0].y-rgbli[1].y),2) + pow((rgbli[0].z-rgbli[1].z),2));
                    for(j=0; j<sayi; j++)
                    {
                        for(m=j+1; m<sayi; m++)
                        {
                            if(sqrt(pow((rgbli[j].x-rgbli[m].x),2) + pow((rgbli[j].y-rgbli[m].y),2) + pow((rgbli[j].z-rgbli[m].z),2))<en_yakin_mesafe)
                            {
                                en_yakin_mesafe=sqrt(pow((rgbli[j].x-rgbli[m].x),2) + pow((rgbli[j].y-rgbli[m].y),2) + pow((rgbli[j].z-rgbli[m].z),2));
                                yindis1=j;
                                yindis2=m;
                            }

                        }

                    }

                    printf("En yakin mesafe=%f \n",en_yakin_mesafe);
                    fprintf(cikti,"Basliktaki ve dosyadaki nokta sayisi uyumlu degildir.\n",en_yakin_mesafe);
                    printf("Yakin nokta bilgileri:\n");
                    fprintf(cikti,"Yakin nokta bilgileri:\n");
                    printf(" 1.NOKTA : %f %f %f\n",rgbli[yindis1].x,rgbli[yindis1].y,rgbli[yindis1].z,rgbli[yindis1].r,rgbli[yindis1].g,rgbli[yindis1].b);
                    fprintf(cikti," 1.NOKTA : %f %f %f\n",rgbli[yindis1].x,rgbli[yindis1].y,rgbli[yindis1].z,rgbli[yindis1].r,rgbli[yindis1].g,rgbli[yindis1].b);
                    printf(" 2.NOKTA : %f %f %f\n",rgbli[yindis2].x,rgbli[yindis2].y,rgbli[yindis2].z,rgbli[yindis2].r,rgbli[yindis2].g,rgbli[yindis2].b);
                    fprintf(cikti," 2.NOKTA : %f %f %f\n",rgbli[yindis2].x,rgbli[yindis2].y,rgbli[yindis2].z,rgbli[yindis2].r,rgbli[yindis2].g,rgbli[yindis2].b);


                    en_uzak_mesafe=sqrt(pow((rgbli[0].x-rgbli[1].x),2) + pow((rgbli[0].y-rgbli[1].y),2) + pow((rgbli[0].z-rgbli[1].z),2));

                    for(j=0; j<sayi; j++)
                    {
                        for(m=j+1; m<sayi; m++)
                        {


                            if(sqrt(pow((rgbli[j].x-rgbli[m].x),2) + pow((rgbli[j].y-rgbli[m].y),2) + pow((rgbli[j].z-rgbli[m].z),2))>en_uzak_mesafe)
                            {
                                en_uzak_mesafe=sqrt(pow((rgbli[j].x-rgbli[m].x),2) + pow((rgbli[j].y-rgbli[m].y),2) + pow((rgbli[j].z-rgbli[m].z),2));
                                uindis1=j;
                                uindis2=m;
                            }

                      }

                    }
                     printf("En uzak mesafe:%f \n",en_uzak_mesafe);
                     fprintf(cikti,"En uzak mesafe:%f \n",en_uzak_mesafe);
                    printf("Uzak nokta bilgileri:\n");
                    fprintf(cikti,"Uzak nokta bilgileri:\n");
                    printf(" 1.NOKTA : %f %f %f\n",rgbli[uindis1].x,rgbli[uindis1].y,rgbli[uindis1].z,rgbli[uindis1].r,rgbli[uindis1].g,rgbli[uindis1].b);
                    fprintf(cikti," 1.NOKTA : %f %f %f\n",rgbli[uindis1].x,rgbli[uindis1].y,rgbli[uindis1].z,rgbli[uindis1].r,rgbli[uindis1].g,rgbli[uindis1].b);
                    printf(" 2.NOKTA : %f %f %f\n",rgbli[uindis2].x,rgbli[uindis2].y,rgbli[uindis2].z,rgbli[uindis2].r,rgbli[uindis2].g,rgbli[uindis2].b);
                    fprintf(cikti," 2.NOKTA : %f %f %f\n",rgbli[uindis2].x,rgbli[uindis2].y,rgbli[uindis2].z,rgbli[uindis2].r,rgbli[uindis2].g,rgbli[uindis2].b);


                }
                else if(kontrol == 0){

                    en_yakin_mesafe=sqrt(pow((renksiz_n[0].x-renksiz_n[1].x),2) + pow((renksiz_n[0].y-renksiz_n[1].y),2) + pow((renksiz_n[0].z-renksiz_n[1].z),2));
                    for(j=0; j<sayi; j++)
                    {
                        for(m=j+1; m<sayi; m++)
                        {
                            if(sqrt(pow((renksiz_n[j].x-renksiz_n[m].x),2) + pow((renksiz_n[j].y-renksiz_n[m].y),2) + pow((renksiz_n[j].z-renksiz_n[m].z),2))<en_yakin_mesafe)
                            {
                                en_yakin_mesafe=sqrt(pow((renksiz_n[j].x-renksiz_n[m].x),2) + pow((renksiz_n[j].y-renksiz_n[m].y),2) + pow((renksiz_n[j].z-renksiz_n[m].z),2));
                                yindis1=j;
                                yindis2=m;
                            }

                        }

                    }

                    printf("En yakin mesafe=%f \n",en_yakin_mesafe);
                    fprintf(cikti,"En yakin mesafe=%f \n",en_yakin_mesafe);
                    printf("Yakin nokta bilgileri:\n");
                    fprintf(cikti,"Yakin nokta bilgileri:\n");
                    printf(" 1.NOKTA : %f %f %f\n",renksiz_n[yindis1].x,renksiz_n[yindis1].y,renksiz_n[yindis1].z);
                    fprintf(cikti," 1.NOKTA : %f %f %f\n",renksiz_n[yindis1].x,renksiz_n[yindis1].y,renksiz_n[yindis1].z);
                    printf(" 2.NOKTA : %f %f %f\n",renksiz_n[yindis2].x,renksiz_n[yindis2].y,renksiz_n[yindis2].z);
                    fprintf(cikti," 2.NOKTA : %f %f %f\n",renksiz_n[yindis2].x,renksiz_n[yindis2].y,renksiz_n[yindis2].z);


                    en_uzak_mesafe=sqrt(pow((renksiz_n[0].x-renksiz_n[1].x),2) + pow((renksiz_n[0].y-renksiz_n[1].y),2) + pow((renksiz_n[0].z-renksiz_n[1].z),2));
                    for(j=0; j<sayi; j++)
                    {
                        for(m=j+1; m<sayi; m++)
                        {


                            if(sqrt(pow((renksiz_n[j].x-renksiz_n[m].x),2) + pow((renksiz_n[j].y-renksiz_n[m].y),2) + pow((renksiz_n[j].z-renksiz_n[m].z),2))>en_uzak_mesafe)
                            {
                                en_uzak_mesafe=sqrt(pow((renksiz_n[j].x-renksiz_n[m].x),2) + pow((renksiz_n[j].y-renksiz_n[m].y),2) + pow((renksiz_n[j].z-renksiz_n[m].z),2));
                                uindis1=j;
                                uindis2=m;
                            }

                      }

                    }
                     printf("En uzak mesafe:%f \n",en_uzak_mesafe);
                     fprintf(cikti,"En uzak mesafe:%f \n",en_uzak_mesafe);
                    printf("Uzak nokta bilgileri:\n");
                    fprintf(cikti,"Uzak nokta bilgileri:\n");
                    printf(" 1.NOKTA : %f %f %f\n",renksiz_n[uindis1].x,renksiz_n[uindis1].y,renksiz_n[uindis1].z);
                    fprintf(cikti," 1.NOKTA : %f %f %f\n",renksiz_n[uindis1].x,renksiz_n[uindis1].y,renksiz_n[uindis1].z);
                    printf(" 2.NOKTA : %f %f %f\n",renksiz_n[uindis2].x,renksiz_n[uindis2].y,renksiz_n[uindis2].z);
                    fprintf(cikti," 2.NOKTA : %f %f %f\n",renksiz_n[uindis2].x,renksiz_n[uindis2].y,renksiz_n[uindis2].z);

                }

            }
            printf("\n");
            fprintf(cikti,"\n");

            if(secim == 3)
            {
                if(kontrol == 1)
                {
                    en_kucuk_x=rgbli[0].x;
                    en_kucuk_y=rgbli[0].y;
                    en_kucuk_z=rgbli[0].z;

                    for(j=0; j<sayi; j++)
                    {
                        if(rgbli[j].x<en_kucuk_x)
                        {
                            en_kucuk_x=rgbli[j].x;
                        }
                        if(rgbli[j].y<en_kucuk_y)
                        {
                            en_kucuk_y=rgbli[j].y;
                        }
                        if(rgbli[j].z<en_kucuk_z)
                        {
                            en_kucuk_z=rgbli[j].z;
                        }
                    }
                    printf("En kucuk x:%f\n",en_kucuk_x);
                    fprintf(cikti,"En kucuk x:%f\n",en_kucuk_x);
                    printf("En kucuk y=%f\n",en_kucuk_y);
                    fprintf(cikti,"En kucuk y:%f\n",en_kucuk_y);
                    printf("En kucuk z:%f\n",en_kucuk_z);
                    fprintf(cikti,"En kucuk z:%f\n",en_kucuk_z);
                    printf("\n");
                    fprintf(cikti,"\n");
                    en_buyuk_x=rgbli[0].x;
                    en_buyuk_y=rgbli[0].y;
                    en_buyuk_z=rgbli[0].z;

                    for(j=0; j<sayi; j++)
                    {
                        if(rgbli[j].x>en_buyuk_x)
                        {
                            en_buyuk_x=rgbli[j].x;
                        }
                        if(rgbli[j].y>en_buyuk_y)
                        {
                            en_buyuk_y=rgbli[j].y;
                        }
                        if(rgbli[j].z>en_buyuk_z)
                        {
                            en_buyuk_z=rgbli[j].z;
                        }
                    }
                    printf("En buyuk x:%f\n",en_buyuk_x);
                    fprintf(cikti,"En buyuk x:%f\n",en_buyuk_x);
                    printf("En buyuk y=%f\n",en_buyuk_y);
                    fprintf(cikti,"En buyuk y:%f\n",en_buyuk_y);
                    printf("En buyuk z:%f\n",en_buyuk_z);
                    fprintf(cikti,"En buyuk z:%f\n",en_buyuk_z);

                    printf("\n");
                    fprintf(cikti,"\n");
                    if(en_buyuk_x>en_buyuk_y && en_buyuk_x>en_buyuk_z)
                    {
                        en_buyuk_y=en_buyuk_x;
                        en_buyuk_z=en_buyuk_x;
                    }
                    else if(en_buyuk_y>en_buyuk_x && en_buyuk_y>en_buyuk_z)
                    {
                        en_buyuk_x=en_buyuk_y;
                        en_buyuk_z=en_buyuk_y;
                    }
                    else if(en_buyuk_z>en_buyuk_x && en_buyuk_z>en_buyuk_y)
                    {
                        en_buyuk_x=en_buyuk_z;
                        en_buyuk_y=en_buyuk_z;
                    }
                    else if(en_kucuk_x<en_kucuk_y && en_kucuk_x<en_kucuk_z)
                    {
                        en_kucuk_y=en_kucuk_x;
                        en_kucuk_z=en_kucuk_x;
                    }
                    else if(en_kucuk_y<en_kucuk_x && en_kucuk_y<en_kucuk_z)
                    {
                        en_kucuk_x=en_kucuk_y;
                        en_kucuk_z=en_kucuk_y;
                    }
                    else if(en_kucuk_z<en_kucuk_x && en_kucuk_z<en_kucuk_y)
                    {
                        en_kucuk_x=en_kucuk_z;
                        en_kucuk_y=en_kucuk_z;
                    }
                    printf("1. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_kucuk_z);
                    fprintf(cikti,"1. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_kucuk_z);
                    printf("2. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_kucuk_z);
                    fprintf(cikti,"2. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_kucuk_z);
                    printf("3. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_kucuk_z);
                    fprintf(cikti,"3. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_kucuk_z);
                    printf("4. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_buyuk_z);
                    fprintf(cikti,"4. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_buyuk_z);
                    printf("5. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_kucuk_z);
                    fprintf(cikti,"5. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_kucuk_z);
                    printf("6. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_buyuk_z);
                    fprintf(cikti,"6. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_buyuk_z);
                    printf("7. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_buyuk_z);
                    fprintf(cikti,"7. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_buyuk_z);
                    printf("8. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_buyuk_z);
                    fprintf(cikti,"8. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_buyuk_z);

                }
                else if(kontrol == 0)
                {
                    en_kucuk_x=renksiz_n[0].x;
                    en_kucuk_y=renksiz_n[0].y;
                    en_kucuk_z=renksiz_n[0].z;

                    for(j=0; j<sayi; j++)
                    {
                        if(renksiz_n[j].x<en_kucuk_x)
                        {
                            en_kucuk_x=renksiz_n[j].x;
                        }
                         if(renksiz_n[j].y<en_kucuk_y)
                        {
                            en_kucuk_y=renksiz_n[j].y;
                        }
                         if(renksiz_n[j].z<en_kucuk_z)
                        {
                            en_kucuk_z=renksiz_n[j].z;
                        }
                    }
                    printf("En kucuk x:%f\n",en_kucuk_x);
                    fprintf(cikti,"En kucuk x:%f\n",en_kucuk_x);
                    printf("En kucuk y=%f\n",en_kucuk_y);
                    fprintf(cikti,"En kucuk y:%f\n",en_kucuk_y);
                    printf("En kucuk z:%f\n",en_kucuk_z);
                    fprintf(cikti,"En kucuk z:%f\n",en_kucuk_z);
                    printf("\n");
                    fprintf(cikti,"\n");
                    en_buyuk_x=renksiz_n[0].x;
                    en_buyuk_y=renksiz_n[0].y;
                    en_buyuk_z=renksiz_n[0].z;

                    for(j=0; j<sayi; j++)
                    {
                        if(renksiz_n[j].x>en_buyuk_x)
                        {
                            en_buyuk_x=renksiz_n[j].x;
                        }
                        else if(renksiz_n[j].y>en_buyuk_y)
                        {
                            en_buyuk_y=renksiz_n[j].y;
                        }
                        else if(renksiz_n[j].z>en_buyuk_z)
                        {
                            en_buyuk_z=renksiz_n[j].z;
                        }
                    }
                    printf("En buyuk x:%f\n",en_buyuk_x);
                    fprintf(cikti,"En buyuk x:%f\n",en_buyuk_x);
                    printf("En buyuk y=%f\n",en_buyuk_y);
                    fprintf(cikti,"En buyuk y:%f\n",en_buyuk_y);
                    printf("En buyuk z:%f\n",en_buyuk_z);
                    fprintf(cikti,"En buyuk z:%f\n",en_buyuk_z);

                    printf("\n");
                    if(en_buyuk_x>en_buyuk_y && en_buyuk_x>en_buyuk_z)
                    {
                        en_buyuk_y=en_buyuk_x;
                        en_buyuk_z=en_buyuk_x;
                    }
                    else if(en_buyuk_y>en_buyuk_x && en_buyuk_y>en_buyuk_z)
                    {
                        en_buyuk_x=en_buyuk_y;
                        en_buyuk_z=en_buyuk_y;
                    }
                    else if(en_buyuk_z>en_buyuk_x && en_buyuk_z>en_buyuk_y)
                    {
                        en_buyuk_x=en_buyuk_z;
                        en_buyuk_y=en_buyuk_z;
                    }
                    else if(en_kucuk_x<en_kucuk_y && en_kucuk_x<en_kucuk_z)
                    {
                        en_kucuk_y=en_kucuk_x;
                        en_kucuk_z=en_kucuk_x;
                    }
                    else if(en_kucuk_y<en_kucuk_x && en_kucuk_y<en_kucuk_z)
                    {
                        en_kucuk_x=en_kucuk_y;
                        en_kucuk_z=en_kucuk_y;
                    }
                    else if(en_kucuk_z<en_kucuk_x && en_kucuk_z<en_kucuk_y)
                    {
                        en_kucuk_x=en_kucuk_z;
                        en_kucuk_y=en_kucuk_z;
                    }
                    printf("1. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_kucuk_z);
                    fprintf(cikti,"1. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_kucuk_z);
                    printf("2. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_kucuk_z);
                    fprintf(cikti,"2. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_kucuk_z);
                    printf("3. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_kucuk_z);
                    fprintf(cikti,"3. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_kucuk_z);
                    printf("4. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_buyuk_z);
                    fprintf(cikti,"4. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_buyuk_y,en_buyuk_z);
                    printf("5. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_kucuk_z);
                    fprintf(cikti,"5. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_kucuk_z);
                    printf("6. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_buyuk_z);
                    fprintf(cikti,"6. kosenin koordinatlari: %f %f %f\n",en_buyuk_x,en_kucuk_y,en_buyuk_z);
                    printf("7. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_buyuk_z);
                    fprintf(cikti,"7. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_kucuk_y,en_buyuk_z);
                    printf("8. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_buyuk_z);
                    fprintf(cikti,"8. kosenin koordinatlari: %f %f %f\n",en_kucuk_x,en_buyuk_y,en_buyuk_z);
                }
            }
            printf("\n");
            fprintf(cikti,"\n");
            if(secim == 4)
            {
                printf("KURE OLUSTURMA: \n\n");
                fprintf(cikti,"KURE OLUSTURMA: \n\n");
                if(kure_sayaci==0){
                printf("Kurenin merkez x y z bilgilerinin giriniz:\n");
                scanf("%f %f %f",&kure_x,&kure_y,&kure_z);
                printf("Kurenin yaricapini giriniz:");
                scanf("%f",&yaricap);
                kure_sayaci++;
                }
                fprintf(cikti,"Merkez X Y Z: %f %f %f\nYaricap: %f\n",kure_x,kure_y,kure_z,yaricap);
                if(kontrol==1)
                {
                    for(j=0 ; j<sayi ; j++)
                    {
                        kure_uzaklik = sqrt(pow((kure_x-rgbli[j].x),2) + pow((kure_y-rgbli[j].y),2) + pow((kure_z-rgbli[j].z),2));

                        if(kure_uzaklik<yaricap)
                        {

                            printf("%f %f %f\n",rgbli[j].x,rgbli[j].y,rgbli[j].z);
                            fprintf(cikti,"%f %f %f\n",rgbli[j].x,rgbli[j].y,rgbli[j].z);

                        }
                    }

                }
                else if(kontrol == 0)
                {

                    for(j=0 ; j<sayi ; j++)
                    {
                        kure_uzaklik = sqrt(pow((kure_x-renksiz_n[j].x),2) + pow((kure_y-renksiz_n[j].y),2) + pow((kure_z-renksiz_n[j].z),2));

                        if(kure_uzaklik<yaricap)
                        {

                            printf("%f %f %f\n",renksiz_n[j].x,renksiz_n[j].y,renksiz_n[j].z);
                            fprintf(cikti,"%f %f %f\n",renksiz_n[j].x,renksiz_n[j].y,renksiz_n[j].z);

                        }
                    }

                }
            }
            printf("\n");
            fprintf(cikti,"\n");
            if(secim == 5)
            {
                if(kontrol== 1)
                {
                    for(j=0;j<sayi;j++)
                    {
                        for(m=j+1;m<sayi;m++)
                        {
                            uzaklik = sqrt(pow((rgbli[j].x-rgbli[m].x),2) + pow((rgbli[j].y-rgbli[m].y),2) + pow((rgbli[j].z-rgbli[m].z),2));
                            toplam +=uzaklik;
                        }
                    }
                    ortalama = toplam/((sayi*(sayi-1)/2));

                    printf("Ortalama: %f\n\n",ortalama);
                    fprintf(cikti,"Ortalama: %f\n\n",ortalama);

                }
                else if(kontrol == 0)
                {

                    for(j=0;j<sayi;j++)
                    {
                        for(m=j+1;m<sayi;m++)
                        {
                            uzaklik = sqrt(pow((renksiz_n[j].x-renksiz_n[m].x),2) + pow((renksiz_n[j].y-renksiz_n[m].y),2) + pow((renksiz_n[j].z - renksiz_n[m].z),2));
                            toplam +=uzaklik;
                        }
                    }
                    ortalama = toplam/((sayi*(sayi-1)/2));

                    printf("Ortalama: %f\n\n",ortalama);
                    fprintf(cikti,"Ortalama: %f\n\n",ortalama);

                }


            }
            if(secim==6)
            {
                printf("\n-------------------------------------\n\n");
                fprintf(cikti,"\n-------------------------------------\n\n");
                break;

            }

// while(1)
    }



// binary nin
    }

    }

    }

    return 0;
}
