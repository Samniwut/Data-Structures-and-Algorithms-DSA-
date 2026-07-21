/* 
Program create array 1-3 dimension in function by..
1. Calculate and Allocate memory
2. Calculate the memoryaddress of array 
3. Use point directed in to memory and read/write its
4. Formular useing
Element = (u-l+1)
Element = (u1-l1+1)*(u2-l2+1)
Element = (u1-l1+1)*(u2-l2+1)*(u3-l3+1)
Total_mem = Element*C
Address of Array
A(i) =BA+(i-l)C
A(i,j) =BA+(i-l1)*(u2-l2+1)C+(j-l2)C
A(i,j,k)=BA+(i-l1)*(u2-l2+1)(u3-l3+1)C+(j-l2)(u3-l3+1)C+(k-l3)C
===================================================================*/
#include <stdio.h> //use printf()
#include <stdlib.h>//use malloc()
#define l 1 //lower Bound 
#define u 5 //Upper Bound 
#define l1 1 //lower Bound 1
#define u1 3 //Upper Bound 1
#define l2 1 //Lower Bound 2
#define u2 4 //Upper Bound 2
#define l3 1 //Lower Bound 3
#define u3 5 //Upper Bound 3
int *BA1, *BA2, *BA3, *p , *BA4; //Base address of each dimension and moving pointer
int i,j,k,number; //subscript of Array 
void Create1DArray(){ //Create Array 1 dimension
 int element,c,total_mem; //Variable uses 
 element=(u-l+1); //Calculate element
 c=sizeof(*BA1); //Calculate Size each block of Array
 total_mem=element*c; //Calculate Total Size
 BA1=(int*)malloc(total_mem); //Memory allocate and use BA1 to point to its
} 
void A1(int i,int x){ //Put data into Array 1 Dimension
 p=BA1+(i-l); //Calculate pointer 
 *p=x; //Put data 
} 
int ReadA1(int i) { //Read data from Array 1 Dimension
 p=BA1+(i-l); //Calculate pointer
 return(*p); //Return value in Array
} 
//---------------------------------------------------------------------
void print_Plane_Column_Row_Nextstes(int plane,int Column, int row){
   int plane_byte = plane*4 ; 
   int Column_byte = Column*4 ; 
   int row_byte = row*4 ; 
   printf("\nPlane--> %d \n",plane);
   printf("Column--> %d  \n",Column);
   printf("Row--> %d \n",row);

}
//---------------------------------------------------------------------
void Create2DArray() { 
 int element,c,total_mem; 
 element=(u1-l1+1)*(u2-l2+1); 
 c=sizeof(*BA2); 
 total_mem=element*c; 
 BA2=(int*)malloc(total_mem); 
} 
void A2(int i,int j,int x) { 
 p=BA2+((i-l1)*(u2-l2+1)+(j-l2)); 
 *p=x; 
} 
int ReadA2(int i,int j) { 
 p=BA2+(i-l1)*(u2-l2+1)+(j-l2); 
 return(*p); 
} 
//---------------------------------------------------------------------
void Create3DArray() { 
 int element,c,total_mem; 
 element=(u1-l1+1)*(u2-l2+1)*(u3-l3+1); 
 c=sizeof(*BA3); 
 total_mem=element*c; 
 BA3=(int*)malloc(total_mem); 
} 
void A3(int i,int j,int k,int x) { //Palane-Row-Column
 p=BA3+((i-l1)*(u2-l2+1)*(u3-l3+1)+(j-l2)*(u3-l3+1)+(k-l3)); 
 *p=x; 
} 
int ReadA3(int i,int j,int k){
 p=BA3+(i-l1)*(u2-l2+1)*(u3-l3+1)+(j-l2)*(u3-l3+1)+(k-l3);
 return(*p);
} 
//---------------------------------------------------------------------
void Create3DArray_V4(){ // Row-Plane-Column
 int element,c,total_mem; 
 element=(u1-l1+1)*(u2-l2+1)*(u3-l3+1); 
 c=sizeof(*BA4); 
 total_mem=element*c; 
 BA4=(int*)malloc(total_mem);
  printf("\nelement %d",element);

}
void A4(int i,int j,int k,int x) { 
 p=BA4+((j-l2)*(u1-l1+1)*(u3-l3+1)+(i-l1)*(u3-l3+1)+(k-l3)); 
 *p=x; 
} 
int ReadA4(int i,int j,int k){
 p=BA4+(j-l2)*(u1-l1+1)*(u3-l3+1)+(i-l1)*(u3-l3+1)+(k-l3);
 return(*p);
}
void print_br(){
    printf("\n============================\n");
}
//---------------------------------------------------------------------
// ฟังชั่นหา Plane, Row, Column จาก offset (3D Array: Plane-Row-Column)
void GetIndices3D_PRC(long offset, int *pi, int *pj, int *pk) {
    int row_size = (u2-l2+1);  // 4
    int col_size = (u3-l3+1);  // 5

    int plane = offset / (row_size * col_size);
    long remainder1 = offset % (row_size * col_size);

    int row = remainder1 / col_size;
    int col = remainder1 % col_size;

    printf("\n--- การคำนวณแต่ละลำดับ ---");
    printf("\n Plane = %d (Plane)",plane);
    printf("\n Row = %d (Row)",row);
    printf("\n Column = %d (Column)",col);

    *pi = plane + l1;
    *pj = row + l2;
    *pk = col + l3;
}
//---------------------------------------------------------------------
// ฟังชั่นหา Plane, Row, Column จาก offset (3D Array: Row-Plane-Column)
void GetIndices3D_RPC(long offset, int *pi, int *pj, int *pk) {
    int plane_size = (u1-l1+1);  // 3
    int col_size = (u3-l3+1);    // 5

    int row = offset / (plane_size * col_size);
    long remainder1 = offset % (plane_size * col_size);

    int plane = remainder1 / col_size;
    int col = remainder1 % col_size;

    printf("\n--- การคำนวณแต่ละลำดับ ---");
    printf("\n Row = %d (Row)",row);
    printf("\n Plane = %d (Plane)",plane);
    printf("\n Column = %d (Column)",col);

    *pi = plane + l1;
    *pj = row + l2;
    *pk = col + l3;
}

//---------------------------------------------------------------------
int main() { 
 printf("1-3 DIMENSION ARRAY FUNCTION...\n"); 
 printf("=================================\n"); 
// Create Array.........
 Create1DArray(); 
 Create2DArray(); 
 Create3DArray(); 
 Create3DArray_V4();
// //Using 1 Dimention Array...
//  i=2;
//  number = 9;
//  A1(i,number);
//  printf("\nA1(%d) = %d ",i,ReadA1(i)); 
//  printf("\nBA1 = %p",&BA1);
//  printf("\nAddress for --> %d <-- = %p",number,p);
//  print_br();
// //Using 2 Dimension Array ...
//  i=2; j=3; number = 99;
//  A2(i,j,number); 
//  printf("\nA2(%d,%d) = %d ",i,j,ReadA2(i,j)); 
//  printf("\nBA2 = %p",&BA2);
//  printf("\nAddress for --> %d <-- = %p",number,p);
//  print_br();
//Using 3 Dimension Array...
 i=3; j=3;k=3; number = 999;
 printf("\n(Palane-Row-Column)"); 
 A3(i,j,k,number); 

 printf("\nA3(%d,%d,%d) ข้อมูล %d ",i,j,k,ReadA3(i,j,k)); 
//  printf("\nBA3 = %p ",&BA3);
//  printf("\nAddress for --> %d <-- = %p",number,p);
 long offset_A3 = (long)(p - BA3);
 printf("\n ข้อมูลอยู่ช่องที่ = %ld", offset_A3);
 int orig_i = i, orig_j = j, orig_k = k;
 GetIndices3D_PRC(offset_A3, &i, &j, &k);
 print_br();
 //Using 3 Dimension Array... v4
 printf("\n(Row-Plane-Column)"); // แสดงข้อความว่าฟั่งชั่นทำงานแบบไหน
 i=3;j=3;k=3; number = 99;  // set value เข้าฟั่งชั่น
 A4(i,j,k,number);   // ส่งค่าเข้าฟั่งชั่น A4

 printf("\nA4(%d,%d,%d) ข้อมูล %d ",i,j,k,ReadA4(i,j,k));  //แสดงผลลัพที่ส่งเข้าไปใน ฟั่งชั่น ReadA4
 // printf("\nBA4 = %p",&BA4); // แสดงที่อยู่เริ่มต้นของ BA4
//  printf("\nAddress for --> %d <-- = %p",number,p); // แสดงที่อยู่สุดท้ายของ Array ที่สร้างไว้
 long offset_A4 = (long)(p - BA4);
 printf("\nข้อมูลอยู่ช่องที่ = %ld", offset_A4); // แสดงจำนวนช่องของ Array ที่สร้างไว้
 orig_i = i; orig_j = j; orig_k = k;
 GetIndices3D_RPC(offset_A4, &i, &j, &k);

 print_br();//เว้นบรรทัด
 getchar(); //Wait for KBD hit
 free(BA1); //Free memory of each array
 free(BA2); //Free memory of each array
 free(BA3); //Free memory of each array
 free(BA4); //Free memory of each array
 return(0); 
} //End MAIN Fn.