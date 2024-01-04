#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
int tahta_boyutu = 0;
int mayin_sayisi = 0;
char **tahta;
char **final;
int o_satir = 0;
int o_sutun = 0;
int oyun_durumu = 1;

char **mayin_uret(char **_tahta, int mayin_sayisi)
{
  int i = 1;
  while (i <= mayin_sayisi)
  {
    int satir = rand() % tahta_boyutu;
    int sutun = rand() % tahta_boyutu;
    if (_tahta[satir][sutun] != 'G' && _tahta[satir][sutun] != 'C' && _tahta[satir][sutun] != 'o' && _tahta[satir][sutun] != 'x')
    {

      _tahta[satir][sutun] = 'o';
      if (satir < tahta_boyutu - 1)
      {
        _tahta[satir + 1][sutun] = 'x';
      }
      if (satir > 0)
      {
        _tahta[satir - 1][sutun] = 'x';
      }
      if (sutun < tahta_boyutu - 1)
      {
        _tahta[satir][sutun + 1] = 'x';
      }
      if (sutun > 0)
      {
        _tahta[satir][sutun - 1] = 'x';
      }
      i++;
    }
  }
  return _tahta;
}
void tahtayi_yazdir(char **_tahta)
{

  _tahta[0][0] = 'G';
  _tahta[tahta_boyutu - 1][tahta_boyutu - 1] = 'C';
  int k = 0;
  while (k < tahta_boyutu) // tahtanın üst index değerleri için yazılmış döngü
  {
    if (k == 0)
    {
      printf("    ");
    }
    printf(" _ _");
    k++;
  }
  printf("\n");

  for (int i = 0; i < tahta_boyutu; i++)
  {
    printf("    |"); // tahtanın sol index değerleri için yazılmış ifade
    for (int j = 0; j < tahta_boyutu; j++)
    {
      printf("_%c_|", _tahta[i][j]); // tahtanın içini yazdıran ifade
    }
    printf("\n");
  }
}

void kontrol()
{
  if (tahta[o_satir][o_sutun] == 'x')
  {
    tahta[o_satir][o_sutun] = ' ';
    final[o_satir][o_sutun] = ' ';
    o_satir = 0;
    o_sutun = 0;
    final[o_satir][o_sutun] = 'i';
    printf("Bomba patladi, girise dondunuz.\n");
  }
  else if (tahta[o_satir][o_sutun] == 'o')
  {
    printf("Oyunu kaybettiniz.\n");
    tahtayi_yazdir(tahta);
    oyun_durumu = 0; // Oyun kaybedildi
  }
  else if (tahta[o_satir][o_sutun] == 'C')
  {
    printf("Oyunu kazandiniz.\n");
    oyun_durumu = 0; // Oyun kazanıldı
    tahtayi_yazdir(tahta);
  }
}
void hareket()
{
  char secim;
  printf("Gitmek istediginiz yonu girin: ");
  secim = getche();
  printf("\n");

  if (secim == 'w' || secim == 'a' || secim == 's' || secim == 'd' || secim == 'k' || secim == 'e')
  {
    switch (secim)
    {
    case 'w':
      if (o_satir > 0) // bu ifade oyuncunun tahta dışına çıkmasını önlüyor
      {
        system("cls");
        o_satir = o_satir - 1;
        final[o_satir][o_sutun] = 'i';
        if (o_satir != tahta_boyutu - 1)
          final[o_satir + 1][o_sutun] = ' ';
        kontrol();
        tahta[o_satir][o_sutun] = '*';
        if (oyun_durumu == 1)
          tahtayi_yazdir(final);
      }
      else
        printf("Lutfen tahtanin disina cikmayin!!!\n");
      break;
    case 's':
      if (o_satir < tahta_boyutu - 1) // bu ifade oyuncunun tahta dışına çıkmasını önlüyor
      {
        system("cls");
        o_satir = o_satir + 1;
        final[o_satir][o_sutun] = 'i';
        if (o_satir != 0)
          final[o_satir - 1][o_sutun] = ' ';
        kontrol();
        tahta[o_satir][o_sutun] = '*';
        if (oyun_durumu == 1)
          tahtayi_yazdir(final);
      }
      else
        printf("Lutfen tahtanin disina cikmayin!!!\n");
      break;

    case 'a':
      if (o_sutun > 0)
      {
        system("cls");
        o_sutun = o_sutun - 1;
        final[o_satir][o_sutun] = 'i';
        if (o_sutun != tahta_boyutu - 1)
          final[o_satir][o_sutun + 1] = ' ';
        kontrol();
        tahta[o_satir][o_sutun] = '*';
        if (oyun_durumu == 1)
          tahtayi_yazdir(final);
      }
      else
        printf("Lutfen tahtanin disina cikmayin!!!\n");
      break;
    case 'd':
      if (o_sutun < tahta_boyutu - 1) // bu ifade oyuncunun tahta dışına çıkmasını önlüyor
      {
        system("cls");
        o_sutun = o_sutun + 1;
        final[o_satir][o_sutun] = 'i';
        if (o_sutun != 0)
          final[o_satir][o_sutun - 1] = ' ';
        kontrol();
        tahta[o_satir][o_sutun] = '*';
        if (oyun_durumu == 1)
          tahtayi_yazdir(final);
      }
      else
        printf("Lutfen tahtanin disina cikmayin!!!\n");
      break;
    case 'k':
      tahtayi_yazdir(tahta);
      break;
    case 'e':
      oyun_durumu = 0; // Oyunu bitir
      break;
    }
  }
}

int main()
{
  short karar = 1;
  while (karar)
  {
    srand(time(NULL));
    printf("Mayin tarlasinin boyutunu girin: ");
    scanf("%d", &tahta_boyutu);
    mayin_sayisi = tahta_boyutu * tahta_boyutu * 0.1;

    // Satırlar için bellek ayırma
    tahta = (char **)malloc(tahta_boyutu * sizeof(char *));
    final = (char **)malloc(tahta_boyutu * sizeof(char *));
    for (int i = 0; i < tahta_boyutu; i++)
    {
      tahta[i] = (char *)malloc(tahta_boyutu * sizeof(char));
      final[i] = (char *)malloc(tahta_boyutu * sizeof(char));
    }

    for (int i = 0; i < tahta_boyutu; i++)
    {
      for (int j = 0; j < tahta_boyutu; j++)
      {
        tahta[i][j] = ' ';
        final[i][j] = ' ';
      }
    }

    tahta[0][0] = 'G';
    tahta[tahta_boyutu - 1][tahta_boyutu - 1] = 'C';
    final[0][0] = 'G';
    final[tahta_boyutu - 1][tahta_boyutu - 1] = 'C';

    tahta = mayin_uret(tahta, mayin_sayisi);
    tahtayi_yazdir(final);

    while (oyun_durumu)
    {
      hareket();
    }

    // Belleği geri bırakma
    for (int i = 0; i < tahta_boyutu; i++)
    {
      free(tahta[i]);
      free(final[i]);
    }
    free(tahta);
    free(final);

    printf("Cikmak icin 0 bastan baslamak icin 1 girin:");
    scanf("%hd", &karar);
    if (karar == 1)
    {
      oyun_durumu = 1;
      o_satir = 0;
      o_sutun = 0;
    }
  }
  return 0;
}
