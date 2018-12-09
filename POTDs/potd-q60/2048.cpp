
#include <iostream>
using namespace std;

void run2048(int puzzle[4][4], int dir) {
    // your code here
    switch(dir){
      case 0://move to left
        for (int i =0;i<4;i++){
          for(int k=0;k<4;k++){//first get rid of zeroes
            if (puzzle[i][k]==0){
              cout<<i<<","<<k<<"=0\n";
              for(int l=k;l<3;l++){puzzle[i][l]=puzzle[i][l+1];}
              puzzle[i][3]=0;
              bool remaining=false;
              for (int l=k;l<4;l++){ if (puzzle[i][l]!=0) remaining=true;}
              if (remaining) k--;//incase a 0 just shifted to new position
            }
            cout<<"sr: "<<puzzle[i][k]<<" ";
          }
          cout<<endl;
          for(int j=0;j<3;j++){//then add numbers if necessary
        //    cout<<"at "<<i<<" "<<j<<endl;
            if (puzzle[i][j]==puzzle[i][j+1]){
          //    cout<<puzzle[i][j]<<"="<<puzzle[i][j+1]<<endl;
              puzzle[i][j]*=2;
            //  cout<<"Now shifting down\n";
              for(int k=j+1;k<3;k++){
                puzzle[i][k]=puzzle[i][k+1];
                //cout<<puzzle[i][j]<<"set to"<<puzzle[i][j+1]<<endl;
              }
              puzzle[i][3]=0;
            }
          }
        }
      break;
      case 1:
        for (int i =0;i<4;i++){
          for(int k=0;k<4;k++){//first get rid of zeroes
            if (puzzle[k][i]==0){
              cout<<i<<","<<k<<"=0\n";
              for(int l=k;l<3;l++){puzzle[l][i]=puzzle[l+1][i];}
              puzzle[3][i]=0;
              bool remaining=false;
              for (int l=k;l<4;l++){ if (puzzle[l][i]!=0) remaining=true;}
              if (remaining) k--;//incase a 0 just shifted to new position
            }
            cout<<"sr: "<<puzzle[k][i]<<" ";
          }
          cout<<endl;
          for(int j=0;j<3;j++){//then add numbers if necessary
        //    cout<<"at "<<i<<" "<<j<<endl;
            if (puzzle[j][i]==puzzle[j+1][i]){
          //    cout<<puzzle[i][j]<<"="<<puzzle[i][j+1]<<endl;
              puzzle[j][i]*=2;
            //  cout<<"Now shifting down\n";
              for(int k=j+1;k<3;k++){
                puzzle[k][i]=puzzle[k+1][i];
                //cout<<puzzle[i][j]<<"set to"<<puzzle[i][j+1]<<endl;
              }
              puzzle[3][i]=0;
            }
          }
        }
    break;
    case 2:
      for (int i =3;i>=0;i--){
        for(int k=3;k>=0;k--){//first get rid of zeroes
          if (puzzle[i][k]==0){
            cout<<i<<","<<k<<"=0\n";
            for(int l=k;l>=1;l--){puzzle[i][l]=puzzle[i][l-1];}
            puzzle[i][0]=0;
            bool remaining=false;
            for (int l=k;l>=1;l--){ if (puzzle[i][l]!=0) remaining=true;}
            if (remaining) k++;//incase a 0 just shifted to new position
          }
          cout<<"sr: "<<puzzle[i][k]<<" ";
        }
        cout<<endl;
        for(int j=4;j>=0;j--){//then add numbers if necessary
      //    cout<<"at "<<i<<" "<<j<<endl;
          if (puzzle[i][j]==puzzle[i][j-1]){
        //    cout<<puzzle[i][j]<<"="<<puzzle[i][j+1]<<endl;
            puzzle[i][j]*=2;
          //  cout<<"Now shifting down\n";
            for(int k=j-1;k>=1;k--){
              puzzle[i][k]=puzzle[i][k-1];
              //cout<<puzzle[i][j]<<"set to"<<puzzle[i][j+1]<<endl;
            }
            puzzle[i][0]=0;
          }
        }
      }
    break;
    case 3:
      for (int i =3;i>=0;i--){
        for(int k=3;k>=0;k--){//first get rid of zeroes
          if (puzzle[k][i]==0){
//            cout<<i<<","<<k<<"=0\n";
            for(int l=k;l>=1;l--){puzzle[l][i]=puzzle[l-1][i];}
            puzzle[0][i]=0;
            bool remaining=false;
            for (int l=k;l>=1;l--){ if (puzzle[l][i]!=0) remaining=true;}
            if (remaining) k++;//incase a 0 just shifted to new position
          }
          cout<<"sr: "<<puzzle[k][i]<<" ";
        }
        cout<<endl;
        for(int j=4;j>=0;j--){//then add numbers if necessary
      //    cout<<"at "<<i<<" "<<j<<endl;
          if (puzzle[j][i]==puzzle[j-1][i]){
        //    cout<<puzzle[i][j]<<"="<<puzzle[i][j+1]<<endl;
            puzzle[j][i]*=2;
          //  cout<<"Now shifting down\n";
            for(int k=j-1;k>=1;k--){
              puzzle[k][i]=puzzle[k-1][i];
              //cout<<puzzle[i][j]<<"set to"<<puzzle[i][j+1]<<endl;
            }
            puzzle[0][i]=0;
          }
        }
      }
    break;
    }
}
