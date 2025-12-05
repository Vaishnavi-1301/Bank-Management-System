#include<stdio.h>
#include<stdlib.h>

struct bankParameter
{
  float totalDeposit;
  float totalLendings;
  float balance;
  float profit;
  float loanRate;
  float savingInterestRate;
  int savingAccountNumberGenerator;
  int loanAccountNumberGenerator;
  int customerIdGenerator;
};

struct bankParameter parameter = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1000, 1000, 1000};

struct account
{
  int customerId;
  int accountNumber;
  char opendate[10];
  char type[10];
  float balance;
};

struct customer
{
  int  id;
  char firstName[10];
  char middleName[10];
  char lastName[10];
  char address[50];
  char mobileNumber[13];
  char email[30];
};

struct transaction
{
  char date[10];
  int transactionId;
  char sourceAccount[7];
  char destinationAccount[10];
  int credit;
  int debit;
};

void displayMenu()
{
    printf("\n\n 1)Create an account. ");
    printf("\n\n 2)Deposit Money ");
    printf("\n\n 3)Withdraw Money");
    printf("\n\n 4)Loan Disbursed ");
    printf("\n\n 5)Balance Check");
    printf("\n\n 6)Money Transfer ");
    printf("\n\n 7)Show bank stats");
    printf("\n\n 8)Exit");

}

void stringCopy(char *source, char* destination)
{
  int i=0;
  while(source[i] != '\0')
  {
    destination[i] = source[i];
    i++;
  }
  destination[i] = source[i];
}

int stringCompare(char *source, char *destination)
{
  int i=0;
  while(source[i] != '\0')
  {
    if(source[i] != destination[i])
    {
      return 0;
    }
    return 1;
  }
}

void createAccount()
{
   FILE *filePointer;
   struct account acc;
   struct customer cust;
   char saving[8] = "Saving";
   char loan[5] = "Loan";
   
   printf("\n\n Enter open date: ");
   scanf("%s", acc.opendate);
   
   printf("\n\n Which account do you want to open? Saving / Loan ");
   scanf("%s", acc.type);
   if(stringCompare(acc.type,"Saving") || stringCompare(acc.type,"saving"))
   {
      printf("\n\n Enter your initial balance: ");
      scanf("%f", &acc.balance);
      
      acc.customerId = parameter.customerIdGenerator;
      acc.accountNumber = parameter.savingAccountNumberGenerator;
      parameter.savingAccountNumberGenerator = parameter.savingAccountNumberGenerator + 1;
      
      parameter.totalDeposit = parameter.totalDeposit + acc.balance; 
   }
   else if(stringCompare(acc.type,"Loan") || stringCompare(acc.type,"loan"))
   {
          
      printf("\n\n Enter your loan disbursement amount: ");
      scanf("%f", &acc.balance);
      
      if(acc.balance > parameter.balance)
      {
        printf("Cannot disburse loan as amount you entered is more than the bank can disbursed");
        return;
      }
      
      //stringCopy(saving, acc.type);
      acc.accountNumber = parameter.loanAccountNumberGenerator;
      parameter.loanAccountNumberGenerator = parameter.loanAccountNumberGenerator + 1;  
      parameter.totalLendings = parameter.totalLendings + acc.balance;
   }
   
  parameter.balance = parameter.totalDeposit - parameter.totalLendings;        
            
  filePointer = fopen("/home/shubham/fileProg/account.bin","ab");
              
  fwrite(&acc, sizeof(struct account), 1, filePointer);
              
  fclose(filePointer);
  
  getchar();
  
  
    cust.id = parameter.customerIdGenerator;
    parameter.customerIdGenerator = parameter.customerIdGenerator + 1;
  
    printf("\n\n Enter Your First Name:  ");
    scanf("%s", cust.firstName);
    
    printf("\n\n Enter Your Middle Name: ");
    scanf("%s", cust.middleName);
    
    printf("\n\n Enter Your last Name: ");
    scanf("%s", cust.lastName);
               
    printf("\n\n Enter your address: ");
    scanf("%s", cust.address);
              
    printf("\n\n Enter your Mobile number: ");
    scanf("%s", cust.mobileNumber);
                
    printf("\n\n Enter your Email-Id: ");
    scanf("%s", cust.email);
                
    filePointer = fopen("/home/shubham/fileProg/customer.bin", "ab"); 
                
    fwrite(&cust, sizeof(struct customer), 1, filePointer);
                
    fclose(filePointer);
                         
    printf("\n\n Account and Customer Information Saved SUCCESSFULLY!!");
    printf("\n\nCustomer Id   : %d",cust.id);
    printf("\nAccount number: %d",acc.accountNumber);
    
    printf("\n");    
}

void moneyDeposit()
{
  int depositAmount;
  int accNumber;
  
  printf("\n\n Enter Account Number: ");
  scanf("%d", &accNumber);

  printf("\n\n Enter amount to deposit : ");
  scanf("%d", &depositAmount);
  
  FILE *filePointer = fopen("/home/shubham/fileProg/account.bin", "rb+");
  
  /*while(fread(&acc, sizeof(struct account), 1, filePointer))
  {
    if(accountNumber == accNumber)
    {
      acc.balance = acc.balance + depositAmount;
      
      
    }
  }*/
  
  printf("\n\n Account number NOT FOUND!!");
  
}

void moneyWithdraw()
{
  int withdrawAmount;
  int accNumber;
  
  printf("\n\n Enter account number: ");
  scanf("%d", &withdrawAmount);
  
  printf("\n\n Enter amount to withdraw: ");
  scanf("%d", &accNumber);
  
  FILE *filePointer = fopen("/home/shubham/fileProg/account.bin","rb+");

}

void initializeBankParameter()
{
    FILE *bankParameterFilePtr = fopen("/home/shubham/fileProg/bankParameter.bin","r");
    
    if(bankParameterFilePtr == NULL)
    {
      bankParameterFilePtr = fopen("/home/shubham/fileProg/bankParameter.bin","w");
      
      fwrite(&parameter, sizeof(struct bankParameter), 1, bankParameterFilePtr);
    }
    else
    {
      fread(&parameter, sizeof(struct bankParameter), 1, bankParameterFilePtr);
    }
    fclose(bankParameterFilePtr);
}

void updateBankParameter()
{
    FILE *bankParameterFilePtr = fopen("/home/shubham/fileProg/bankParameter.bin","w");
    fwrite(&parameter, sizeof(struct bankParameter), 1, bankParameterFilePtr);
    fclose(bankParameterFilePtr);
}


void balanceCheck()
{
  int accNum;
  struct customer cust;
  struct account acc;

  printf("\n\n Enter Account Number: ");
  scanf("%d", &accNum);
  
  FILE *customerFilePtr = fopen("/home/shubham/fileProg/customer.bin", "r");
  FILE *accountFilePtr = fopen("/home/shubham/fileProg/account.bin","r");
  
  while(fread(&acc, sizeof(struct account), 1, accountFilePtr))
  {
    if(accNum == acc.accountNumber)
    {
      while(fread(&cust, sizeof(struct customer), 1, customerFilePtr))
      {
        if(acc.customerId == cust.id)
        {
          printf("\n\n Customer Id = %d ", cust.id);
          printf("\n Account Number = %d ", acc.accountNumber);
          printf("\n Name: %s %s %s ", cust.firstName, cust.middleName, cust.lastName);
          printf("\n Address : %s ", cust.address);
          printf("\n Mobile Number: %s", cust.mobileNumber);
          printf("\n Email: %s ", cust.email );
          printf("\n Account Type: %s ", acc.type);
          printf("\n Account Open Date: %s ", acc.opendate);
          printf("\n Account Balance: %f ", acc.balance);
          printf("\n -----------------------------------");
        }
      }
      return;
    }
  }
  printf("\n\nNo Account Found with Account Number: %d",accNum);
}

int main()
{
  int choice;
  initializeBankParameter();
  
  do
  {
    printf("\n\n\t\t\t\t\t-----------------------------------");
    
    printf("\n\n\t\t\t\t\t\t \"WELCOME TO BANK\"");
    printf("\n\n\t\t\tDeposit: %f INR \tLending: %f INR \tBalance: %f INR",parameter.totalDeposit, parameter.totalLendings, parameter.balance);
    
    printf("\n\n\t\t\t\t\t-----------------------------------");

    displayMenu();
    
    printf("\n\n Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice)
    {
      case 1:       
              createAccount(); 
              updateBankParameter();
      break;
      
      case 2:
              //moneyDeposit();
      break;
      
      case 3: 
              //moneyWithdraw();
      break;
      
      case 4:
              //disbursedLoan();
      break;
      
      case 5:
              balanceCheck();
      break;
      
      case 6:
              //moneyTransfer();
      break;
      
      case 7:
              //bankStatus();
      break;
      
      case 8:
              exit(0);
      break;
      
      default:
              printf("\n\n Please enter valid choice!!");
      break;
    
    }
    
  }while(1);

  return 0;
}
