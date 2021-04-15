
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//pendeklarasian struct sebuah tree awal
typedef struct Node
{
    int data;
    Node *kiri;
    Node *kanan;
};

Node *pohon = NULL;

//fungsi untuk menambahkan node baru
void tambah (Node **root, int databaru)
{
       //jika root masih kosong
    if ((*root)==NULL)
       {
              //pembuatan node baru
        Node *baru;
        //pengalokasian memori dari node yang telah dibuat
        baru = new Node;
        //inisialisasi awal node yang baru dibuat
        baru->data=databaru;
        baru->kiri=NULL;
        baru->kanan=NULL;
        (*root) = baru;
        (*root) -> kiri = NULL;
        (*root) -> kanan = NULL;
        //jika menujuk menunjuk ke NULL artinya tidak mempunyai child
        printf("Data Bertambah!");
       }
    //jika data yang akan dimasukkan lebih kecil daripada elemen root, maka akan diletakkan di node sebelah kiri.
    else if (databaru<(*root)->data)
              tambah(&(*root)->kiri,databaru);
    //jika data yang akan dimasukkan lebih besar daripada elemen root, maka akan diletakkan di node sebelah kanan
    else if (databaru>(*root)->data)
        tambah(&(*root)->kanan,databaru);
    //jika saat dicek data yang akan dimasukkan memiliki nilai yang sama dengan data pada root
    else if (databaru==(*root)->data)
        printf("Data Sudah ada!");
}

//fungsi yang digunakan untuk mencetak tree secara preOrder
void preOrder(Node *root)
{
    if(root!=NULL)
    {
        if(root->data!=NULL)
        {
            printf("%d ",root->data);
        }
        preOrder(root->kiri);
        preOrder(root->kanan);
    }
}

//fungsi yang digunakan untuk mencetak tree secara inOrder
void inOrder(Node *root)
{
       if(root!=NULL)
       {
           inOrder(root->kiri);
           if(root->data!=NULL)
           {
               printf("%d ",root->data);
           }
           inOrder(root->kanan);
        }
}

//fungsi yang digunakan untuk mencetak tree secara postOrder
void postOrder(Node *root)
{
       if(root!=NULL)
       {
         postOrder(root->kiri);
         postOrder(root->kanan);
         if(root->data!=NULL)
         {
            printf("%d ",root->data);
         }
       }
}

//fungsi yang digunakan untuk melakukan pencarian data
void search(Node **root, int cari)
{
    if((*root) == NULL)
    {
        printf("Data tidak ditemukan!");
    }
    //jika data yang dicari lebih kecil dari isi root
    else if(cari < (*root)->data)
        search(&(*root)->kiri,cari);
    //jika data yang dicari lebih besar dari isi root
    else if(cari > (*root)->data)
        search(&(*root)->kanan,cari);
    //jika data yang dicari sama dengan isi dari variabel root
    else if(cari == (*root)->data)
        printf("Data ditemukan!");
}

//fungsi untuk mengetahui jmlah node dalam tree
int count(Node *root)
{
       if(root==NULL)
              return 0;
       else
              return count(root->kiri)+ count(root->kanan)+1;
}

//Fungsi untuk mengetahui ketinggian/kedalaman
int height(Node *root)
{
       if(root == NULL)
              return -1;
       else{
              int u = height(root->kiri);
        int v = height(root->kanan);
        if(u > v)
          return u + 1;
        else
          return v + 1;
       }
}


//fungsi yang digunakan untuk menghapus suatu node
void hapus(Node **root, int del)
{
       Node *curr;
       Node *parent;
       curr = (*root);

       bool flag = false;
  
       while(curr != NULL)
       {
              if(curr->data == del)
              {
                     flag = true;
                     //cout<<"Data ditemukan!";
                      break;
              }
              else
              {
                  parent = curr;
                  if(del>curr->data)
                     curr = curr->kanan;
                  else
                     curr = curr->kiri;
              }
       }

    if(!flag)
    {
        cout<<"Data tidak ditemukan. Penghapusan tidak dilakukan."<<endl;
        return;
    }

       //hanya satu tingkat, dengan kata lain hanya terdapat root
       //jika hanya terdapat root, maka curr node tidak punya parent
       if(height(pohon) == 0)
       {
              if( curr->kiri== NULL && curr->kanan == NULL)
              {
                     (*root) = NULL;
                    
                     return;
              }
       }
       //lebih dari satu tingkat, sehingga node curr mempunyai parent
       else if(height(pohon) > 0)
       {
              //1. jika node yang dihapus tidak memiliki anak
              if( curr->kiri== NULL && curr->kanan == NULL)
              {
                     //jika node merupakan anak kiri dari parent
                     if(parent->kiri == curr)
                     {
                           //replace parent->kiri dengan NULL
                           parent->kiri = NULL;
                           delete curr;
                     }
                     else //jika node merupakan anak kanan dari parent
                     {
                           //replace parent->kanan dengan NULL
                           parent->kanan = NULL;
                           delete curr;
                     }

                     return;
              }

              //2. Jika node memiliki anak tunggal (anak kiri/anak kanan)
              if((curr->kiri == NULL && curr->kanan != NULL)|| (curr->kiri != NULL && curr->kanan == NULL))
              {
                     //jika curr memiliki anak tunggal di sebelah kanan
                     if(curr->kiri == NULL && curr->kanan != NULL)
                     {
                           //jika curr(data yang ingin dihapus) merupakan anak kiri dari parent
                           if(parent->kiri == curr)
                           {
                              //ganti isi parent->kiri dengan curr->kanan
                              parent->kiri = curr->kanan;
                              delete curr;
                         }
                         else //jika curr(data yang ingin dihapus) bukan merupakan anak kiri dari parent
                         {
                              //ganti isi parent->kanan dengan curr->kanan
                              parent->kanan = curr->kanan; 
                              delete curr;
                         }
                     }
                  else //jika curr memiliki anak tunggal di sebelah kiri
                  {
                           //jika curr(data yang ingin dihapus) merupakan anak kiri dari parent
                           if(parent->kiri == curr)
                           {
                                  parent->kiri = curr->kiri; //ganti isi parent->kiri dengan curr->kiri
                                  delete curr;
                           }
                           else //jika curr(data yang ingin dihapus) bukan merupakan anak kiri dari parent
                           {
                               parent->kanan = curr->kiri; //ganti isi parent->kanan dengan curr->kiri
                               delete curr;
                            }
                   }
                   return;
              }


              //3. Node dengan dua anak
              //ganti node dengan nilai terkecil dari Sub Tree Kanan
              if (curr->kiri != NULL && curr->kanan != NULL)
              {
                     //variabel bantu ini digunakan agar posisi curr asli tidak berubah, (tetap pada posisi node yang akan dihapus)
                     //variabel bantu digunakan untuk mengarah ke suatu node
                     Node* bantu;
                     bantu = curr->kanan;

                     //jika subtree kanan dari posisi node sekarang (curr, node yang akan dihapus) tidak memiliki anak
                     if((bantu->kiri == NULL) && (bantu->kanan == NULL))
                     {
                           //ganti node curr dengan bantu
                           // sama dengan curr = (curr->kanan)->kanan |||| semoga tidak bingung :D
                           curr = bantu;
                           delete bantu;
                           curr->kanan = NULL;
                     }
                     else //jika child/anak kanan dari node curr memiliki child
                     {
                           //jika node child kanan dari curr memiliki child kiri
                           if((curr->kanan)->kiri != NULL)
                           {
                                  //variabel bantu ini digunakan agar posisi curr asli tidak berubah, (tetap pada posisi node yang akan dihapus)
                                  //variabel bantu digunakan untuk mengarah ke suatu node
                                  Node* bantu2;
                                  Node* bantu3; //berlaku sebagai parent dari bantu 2
                                  bantu3 = curr->kanan;         //!perhatikan
                                  bantu2 = (curr->kanan)->kiri; //!perhatikan

                                  //mengarahkan posisi node ke node terkiri (untuk menuju ke node yang memiliki nilai terkecil)
                                  while(bantu2->kiri != NULL)
                                  {
                                         bantu3 = bantu2;
                                         bantu2 = bantu2->kiri;
                                  }
                                  //replace nilai dari node curr dengan nilai dari node bantu
                                  curr->data = bantu2->data;
                                  delete bantu2;
                                  bantu3->kiri = NULL;
                        }
                        else //jika node child kanan dari curr tidak memiliki child kiri
                        {
                              Node* tmp;
                              tmp = curr->kanan;
                              //replace nilai dari node curr dengan nilai dari node tmp (curr->kanan)
                              curr->data = tmp->data;
                              curr->kanan = tmp->kanan;
                              delete tmp;
                        }

                     }
                     return;
              }
       }
}

//fungsi utama
int main()
{
    //deklarasikan variabel
    char pil;
    int del,cari;
    while (true)
    {
        system("cls"); //bersihkan layar
        char data;
        printf("\t#PROGRAM TREE C++#");
        printf("\n\t==================");
        printf("\nMENU");
        printf("\n----\n");
        printf("[1] Tambah Data\n");
        printf("[2] Lihat Pre-Order\n");
        printf("[3] Lihat In-Order\n");
        printf("[4] Lihat Post-Order\n");
        printf("[5] Delete\n");
        printf("[6] Kosongkan Data\n");
        printf("[7] Search\n");
        printf("[8] Hitung Node pada Tree\n");
        printf("[9] Kedalaman Tree\n");
        printf("[X] Keluar\n");
        printf("Pilihan Anda : ");
        scanf("%c",&pil);
        fflush(stdin); //mengosongkan buffering
        switch(pil)
        {
            //jika pil bernilai '1'
            case '1':
                     printf("\nINPUT : ");
                     printf("\n-------");
                     printf("\nMasukkan data: ");
                     scanf("%d", &data);
                     //panggil fungsi untuk menambah node yang berisi data pada tree
                     tambah(&pohon,data);
                     _getch();
                      break;

             //jika pil bernilai '2'
              case '2':
                     printf("\nOUTPUT PRE ORDER : ");
                     printf("\n------------------\n");
                     if(pohon!=NULL)
                           //panggil fungsi untuk mencetak data secara preOrder
                           preOrder(pohon);
                     else
                           printf("Masih Kosong!!!");
                    
                     _getch();
                     break;
                    
              //jika pil bernilai '3'
              case '3':
                     printf("\nOUTPUT IN ORDER : ");
                     printf("\n------------------\n");
                     if(pohon!=NULL)
                           //panggil fungsi untuk mencetak data secara inOrder
                           inOrder(pohon);
                     else
                           printf("Masih Kosong!!!");
                    
                     _getch();
                     break;

             //jika pil bernilai '4'
              case '4':
                     printf("\nOUTPUT POST ORDER : ");
                     printf("\n------------------\n");
                     if(pohon!=NULL)
                           //panggil fungsi untuk mencetak data secara postOrder
                           postOrder(pohon);
                     else
                           printf("Masih Kosong!!!");

                     _getch();
                     break;
                  
              //jika pil bernilai '5'
              case '5':
                     if(pohon!=NULL)
                     {
                           printf("\nSEBELUM NODE DIHAPUS : ");
                           printf("\n---------------------- ");
                           //panggil fungsi untuk mencetak data secara preOrder
                           printf("\nPRE ORDER  : ");
                           preOrder(pohon); //panggil fungsi
                           printf("\nIN ORDER   : ");
                           inOrder(pohon); //panggil fungsi
                           printf("\nPOST ORDER : ");
                           postOrder(pohon); //panggil fungsi
                           printf("\n\nPENGHAPUSAN DATA : ");
                           printf("\n------------------\n");
                           printf("Masukkan data yang ingin dihapus: ");
                           scanf("%d", &del);
                        
                          //panggil fungsi yang digunakan untuk melakukan penghapusan pada suatu node
                           hapus(&pohon, del);
                           printf("\n\nSETELAH NODE DIHAPUS : ");
                           printf("\n---------------------- ");
                           printf("\nPRE ORDER  : ");
                           preOrder(pohon); //panggil fungsi
                           printf("\nIN ORDER   : ");
                           inOrder(pohon); //panggil fungsi
                           printf("\nPOST ORDER : ");
                           postOrder(pohon); //panggil fungsi
                     }
                     else
                           printf("\nMasih kosong!");

                     _getch();
                     break;

             //jika pil bernilai '6'
              case '6':
                     pohon=NULL;
                     printf("\nPENGOSONGAN ELEMEN ");
                     printf("\n------------------");
                     printf("\nTree sudah dikosongkan!!");
                      
                     _getch();
                     break;

              //jika pil bernilai '7'
              case '7':
                     printf("\nOUTPUT -> Hanya untuk mengecek apakah data dimaksud terdapat dalam tree");
                     printf("\n------");
                     if(pohon!=NULL)
                     {
                           //panggil fungsi untuk mencetak data secara   preOrder
                           printf("\nPRE ORDER  : ");
                           preOrder(pohon); //panggil fungsi
                           printf("\nIN ORDER   : ");
                           inOrder(pohon); //panggil fungsi
                           printf("\nPOST ORDER : ");
                           postOrder(pohon); //panggil fungsi
                           printf("\n\nPENCARIAN DATA");
                           printf("\n--------------");
                           printf("\nMasukkan data yang ingin dicari : ");
                           scanf("%d", &cari);
                           //panggil fungsi untuk melakukan pencarian data pada tree
                           search(&pohon, cari);
                     }
                     else
                           printf("\nMasih kosong!");

                     _getch();
                     break;

              //jika pil bernilai '8'
              case '8':
                     printf("\nJUMLAH NODE DI DALAM TREE");
                     printf("\n-------------------------");
                     printf("\nJumlah Node :  %d", count(pohon));
                    
                     _getch();
                     break;
           
              //jika pil bernilai '9'
              case '9' :
                     printf("\nKEDALAMAN TREE(LEVEL-> DIMULAI DARI 0)");
                     printf("\n----------------------------------------");
                     printf("\nKedalaman tree : %d\n", height(pohon));
                                   
                     _getch();
                     break;
             
              //jika pil bernilai 'X' atau 'x'
              case 'X'|'x':
                     exit(0);
                     break;
              }
       }
}