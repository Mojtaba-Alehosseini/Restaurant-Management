//Mojtaba Alehoseini ; 9627723 ; Restaurant Project
//Second Semester project for Advance Programming course
//Password: mojtaba

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <windows.h>

using namespace std;

int Food_No_check(int food_no);

class Date
{
public:
	int Day, Month, Year;
};

void print_sleepy(char a[200], int time)
{
    int i;
    for (i=0;a[i]!='\0';i++)
    {
        cout<<a[i];
        Sleep(time);
    }
}

void Please_wait()
{
    for(int i=0;i<10;i++)
    {
        Sleep(100);
        cout<<"\b\b\b";
        cout<<"   ";
        cout<<"\b\b\b";
        cout<<".";
        Sleep(60);
        cout<<".";
        Sleep(55);
        cout<<".";
        Sleep(50);
    }
}

void Upgrading()
{
    int i;
    cout<<"upgrading:\t";
    for(i=0;i<10;i++)
    {
        cout<<i<<"%";
        Sleep(80);
        cout<<"\b\b";
    }
    for(i;i<85;i++)
    {
        cout<<i<<"%";
        Sleep(50);
        cout<<"\b\b\b";
    }
    for(i;i<101;i++)
    {
        cout<<i<<"%";
        Sleep(90);
        cout<<"\b\b\b";
    }
}

int Check_Key(int b)
{
    // b=0 yani register , b=1 yani password
    ofstream CK;
    int i,a,s=0;
    char c[31],plswait[100];
   	if (b==0)
    {
        cout << "\nEnter license key:\n(if you don't have license key, you can buy it from contact us part)\n\t\t\t";
        cin.ignore();
        cin.get(c, 30);
        strcpy(plswait,"Please wait ...");
        print_sleepy(plswait,75);
        Please_wait();
        //Mojtaba
        // Password:  Mojtaba
        for (i = 0; i < 30 && c[i] != '\0'; i++)
        {
            a = int(c[i]);
            s += a;
        }
        if (s == 734)
        {
            CK.open("Registry.mojy", ios::out | ios::binary);
            CK.write((char *)&s , sizeof(int));
            cout<<"\nThanks for buy\n";
            Upgrading();
            return 1;
        }
        cout<<"\a\nWrong license key\n";
        return 0;
    }

}

int Check_Registry()
{
    ifstream CR;
    int f;
    CR.open("Registry.mojy", ios::in | ios::binary);
    if (CR.is_open()!=true)
        return 0;
    CR.read((char *)&f , sizeof(int));
    if (f==734)
        return 1;
    return 0;
}

class Food
{
public:
	char Name[31];
	int Food_No, Price, Mojoodi, Time, food_flag,food_edit_flag;
	Food()
	{
		strcpy(Name, "");
		Food_No = 0;
		Price = 0;
		Mojoodi = 0;
		Time = 0;
		food_flag = 1;
		food_edit_flag=0;
	}
	void Open(void)
	{
		long int file_size(char filename[51]);
		Food_Edit_Open(0);
	}
	void Food_Edit_Open(int a)
	{
	    // a==0 yani az open umade , a!=0 yani az edit umade va a==foodcode hast
		cin.ignore();
		cout << "\nEnter Name:\t";
		gets(Name);
		cout << "Enter Price:\t";
		cin >> Price;
		cout << "Enter Mojoodi:\t";
		cin >> Mojoodi;
		cout << "Enter Maximum Required Time:\t";
		cin >> Time;
		do
        {
            cout << "Enter Food Code:\t";
            cin >> Food_No;
            if (a==0)
            {
                if (Food_No_check(Food_No)==1)
                {
                    cout<<"This Food Code is already exist\n";
                }
                else
                    break;
            }
            if (a!=0)
            {
                if (Food_No==a)
                {
                    break;
                }
                if (Food_No_check(Food_No)==1)
                {
                    cout<<"This Food Code is already exist\n";
                }
                else
                    break;
            }
        }
        while (1==1);
		
	}
};

int Food_No_check(int food_no)
{
    // return 0 yani tekrari nist , 1 yani tekrariye
    ifstream IF;
    Food CF;
    IF.open("Foods.mojy", ios::in | ios::binary);
        if (IF.is_open() != true)
            return 0;
    IF.read((char *)&CF, sizeof(Food));
        while(IF.eof() != true)
        {
            if(CF.Food_No == food_no)
            {
                IF.close();
                return 1;
            }
            IF.read((char *)&CF, sizeof(Food));
        }
        IF.close();
        if(CF.Food_No!=food_no)
        {
            return 0;
        }
}

class edited_Food
{
public:
	char Name[31];
	int Food_No,edited_times;
	// edited times yani chand bar taghir karde, badan too gozaresha azash estefade miknm
	long int Last_Bill_No;
	edited_Food()
	{
		strcpy(Name, "");
		Food_No=edited_times= 0;
		Last_Bill_No = 0;
	}
};

class Customer
{
private:
    char Name[31], LastName[41], Father[31],Phone[12];
    Date DOB;
public:
	int customer_flag;
	long int Account_No;
	Customer()
	{
		strcpy(Name, "");
		strcpy(LastName, "");
		strcpy(Father, "");
		strcpy(Phone, "");
		DOB.Day = DOB.Month = DOB.Year = 0;
		Account_No = 0;
		customer_flag = 1;
	}

	void Open(void)
	{
		long int file_size(char filename[51]);
		Customer_Edit_Open();
		Account_No = 1000 + file_size("Customers.mojy") / sizeof(Customer);
		cout << "\nYour Account Number is:\t" << Account_No;
	}
	void Customer_Edit_Open(void)
	{
		cin.ignore();
		cout << "\nEnter Name:\t";
		gets(Name);
		cout << "Enter Last Name:\t";
		gets(LastName);
		cout << "Enter Father Name:\t";
		gets(Father);
		cout << "Day of Birth:\t";
		cin >> DOB.Day;
		cout << "Month of Birth:\t";
		cin >> DOB.Month;
		cout << "Year of Birth:\t";
		cin >> DOB.Year;
		cout << "Enter Phone Number:\t";
		cin.ignore();
		gets(Phone);
	}
friend    ostream & operator<<(ostream &X, const Customer &A);
};

class Bill
{
public:
    int foods_code[100], prices[100], numbers[100];
    long int Bill_Customer_No, Bill_No;
    Date DOB;
	Bill()
	{
		DOB.Day = DOB.Month = DOB.Year = 0;
		for (int i=0;i<100;i++)
        {
           prices[i]=numbers[i]=foods_code[i]=0;
        }
		Bill_No=Bill_Customer_No=0;
	}
	void DOB_Bill_Open(void)
	{
	  cout << "\nDay:\t";
		cin >> DOB.Day;
		cout << "Month:\t";
		cin >> DOB.Month;
		cout << "Year:\t";
		cin >> DOB.Year;
	}
};

ostream & operator<<(ostream &X, const Customer &A)
{
    X<<"\n| Name: "<<A.Name;
    X<<"\tLast Name: "<<A.LastName;
    X<<"\tPhone: "<<A.Phone;
    X<<"\tAccount No: "<<A.Account_No<<"\t";
    return X;
}

ostream & operator<<(ostream &X, const Food &A)
{
    X<<"\n"<<A.Food_No;
    X<<"\t"<<A.Name;
    X<<"\t"<<A.Price;
    X<<"\t"<<A.Mojoodi;
    X<<"\t\t"<<A.Time;
    return X;
}

void Print_Foods(int a)
{
    // a=0 yani ghazahayi ke pak shodan va mojoodi nadaran chap nashan ---> baraye menu= print deleted and not available
    // a=1 yani pak shodeha chap nashan ---> baraye edit kardan e ghazaha= print all except deleted
    // a=2 hame chap beshan= print all
    Food O;
    ifstream F;
    int mi,ma=0,m;
    F.open("Foods.mojy", ios::in | ios::binary);
	if (F.is_open() != true)
	{
		cout << "Error Opening Foods File.";
	}
	else
        {
            cout<<"\nCode\tName\tPrice\tMojoodi\tMaximum required time";
            cout<<"\n____________________________________________________";
            F.read((char *)&O, sizeof(Food));
            mi=O.Food_No;
            while (F.eof() != true)
                {
                    if (O.Food_No<=mi)
                        mi=O.Food_No;
                    if (O.Food_No>=ma)
                        ma=O.Food_No;
                    F.read((char *)&O, sizeof(Food));
                }
            F.close();
            for (mi;mi<=ma;mi++)
            {
                F.open("Foods.mojy", ios::in | ios::binary);
                F.read((char *)&O, sizeof(Food));
                while (F.eof() != true)
                {
                    if (mi==O.Food_No)
                    {

                        if(mi-m>1)
                            cout<<"\n";
                        if (a==0 && O.Mojoodi!=0 && O.food_flag == 1)
                        {
                            cout << O;
                            m=mi;
                            F.close();
                            break;
                        }

                        if (a==1 && O.food_flag == 1)
                        {
                            cout << O;
                            m=mi;
                            F.close();
                            break;
                        }
                        if (a==2)
                        {
                            cout << O;
                            m=mi;
                            F.close();
                            break;
                        }
                        break;
                    }
                    F.read((char *)&O, sizeof(Food));
                }
                if (F.eof() == true)
                {
                    F.close();
                }
            }
        }
	F.close();
}

int Print_Bill(Bill A , int a, int &c)
{
    // a=0 yani az order= from order , a=1 yani az print all= from print all
    ifstream F,FF,EF;
    Food FB;
    edited_Food EFB;
    int total_prices=0,ch=0,i;
    long int pos;
    F.open("Foods.mojy", ios::in | ios::binary);
    if (F.is_open() != true)
    {
        cout << "Error Opening Foods File.";
    }
    else
    {
        for (i = 0;; i++) // too shart ya i<type ham test miknm badan
        {
            if (A.foods_code[i]==0)
                break;
            cout <<"||\t"<< i + 1 << "-\t";
            // peyda kardane esme ghaza az file ghazaha= finding food name from foods file
            // mishod dakhel for araye 2 bodi begiram va esm haro berizam too oon va alan bejaye search az file az roo oon bekhunam
            // age vaght shod badan inkaro mikonm 4:06 AM 5/31/2018
            F.seekg(0, ios::beg);
            // neshangar file ro mizaram avvale file ta az avval shoro koone be khundan
            F.read((char *)&FB, sizeof(Food));
            while (F.eof() != true)
            {
                if (FB.Food_No == A.foods_code[i])
                {
                    // yani ghaza ro peyda karde
                    if(a==0 || (a==1 && FB.food_edit_flag==0))
                    {
                        pos = F.tellg();
                        pos -= sizeof(FB);
                        F.seekg(pos, ios::beg);
                        cout << FB.Name << "\t";
                        ch=1;
                        break;
                    }
                }
                F.read((char *)&FB, sizeof(Food));
            }
            if (ch==0)
                {
                    EF.open("Edited_Foods.mojy", ios::in | ios::binary);
                    if (EF.is_open() != true)
                    {
                        cout << "\nError Opening Edited Foods File.\n";
                        ch=1;
                        break;
                    }
                    EF.seekg(0,ios::beg);
                    EF.read((char *)&EFB, sizeof(edited_Food));
                    while (EF.eof() != true)
                    {
                        if (A.foods_code[i] == EFB.Food_No)
                        {
                            if (EFB.Last_Bill_No>=A.Bill_No)
                            {
                                // chap e esm e oon ghaza too faktor
                                cout << EFB.Name << "\t";
                                ch=1;
                                break;
                            }
                        }
                        EF.read((char *)&EFB, sizeof(edited_Food));
                    }
                }
            if (ch==0)
            {
                FF.open("Foods.mojy", ios::in | ios::binary);
                // majboor shodam ye istream e dg begiram !! , kar nemikard
                FF.read((char *)&FB, sizeof(Food));
				while (FF.eof() != true)
				{
					if (FB.Food_No == A.foods_code[i])
					{
						// yani ghaza ro peyda karde
                        pos = FF.tellg();
                        pos -= sizeof(FB);
                        FF.seekg(pos, ios::beg);
                        cout << FB.Name << "\t";
                        ch=1;
                        break;
					}
					FF.read((char *)&FB, sizeof(Food));
				}
                // yani file ro ta akhar khoonde vali ghaza ro peyda nakarde
                if (ch==0)
					cout << "\ano such food!!\t";
                // ya file ghaza moshkel darad khat balayi beja esm ghaza chap mishe
                // nemidunam break bezanam ya return ya chi
            }
            // alan esm chap shode hala baghie ro chap miknm

            cout << A.numbers[i] << "\t";
            cout << A.prices[i] << "\t|  ";
            cout << A.numbers[i] * A.prices[i];
            cout << "\t\t\n";
            total_prices += A.numbers[i] * A.prices[i];
            ch=0;
        }
        // } for
        c+=i;
    }
    F.close();
    EF.close();
    FF.close();
    return total_prices;
}

long int file_size(char filename[51])
{
    ifstream X;
    X.open(filename, ios::in|ios::binary);
    if(X.is_open() != true)
    {
        return 0;
    }
    X.seekg(0,ios::end);
    return X.tellg();
}

void Order()
{
	Food O;
	Bill L;
	Customer K;
	ofstream E;
	ifstream F;
	fstream Z;
	int  foodcode = 1, tedad, i, maxtime = 0, types;
	long int pos, total_price = 0;
	char a;
	//chaap ghazaha
    Print_Foods(0);
    // alan ghazaharo neshun dade
    cout << "\nEnter Y to order or any to cancel\t";
	cin.ignore();
	cin.get(a);
	if (a == 'Y' || a == 'y' || a=='1')
	{
		// gofte are sefaresh mide
		for (i = 0; i < 100 ; i++)
		{
			cout << "Enter food code: (Enter 0 to finish ordering)\t";
			cin >> foodcode;
            if (foodcode == 0)
                break;
			// mire too file ghazaha begarde taa peydash kone
            F.open("Foods.mojy", ios::in | ios::binary);
			if (F.is_open() != true)
			{
				cout << "\n\aError Opening Foods File. \tAdd some food first";
				break;
			}
			else
			{
				// file ro peyda karde , shoroo mikne be khundn ta ghaza ro peyda kone
				F.read((char *)&O, sizeof(Food));
				while (F.eof() != true)
				{
					// ta vaghti shomare gaza ro too file peyda kone in halghe tekrar mishe ta akhar file berese
					if (O.Food_No == foodcode)
					{
						pos = F.tellg();
						pos -= sizeof(O);
						cout << "\nHow many " << O.Name << " do you want?:\t";
						cin >> tedad;
						if (tedad > O.Mojoodi)
						{
							do
							{
								cout << "There is not enough "<<O.Name<<", Enter Again (Please enter less than "<<O.Mojoodi<<"):\t";
								cin >> tedad;
								if (tedad==0)
                                    break;
							} while (tedad > O.Mojoodi);
						}
						if (maxtime < O.Time)
							maxtime = O.Time;
						break;
					}
					// } if
					F.read((char *)&O, sizeof(Food));
				}
				// } while
				F.seekg(pos, ios::beg);
				if (tedad==0)
                {
                    i--;
                    F.close();
                    break;
                }
				if (O.Food_No != foodcode)
				{
					cout << "\n no such food\n";
					i--;
					F.close();
				}
				else
				{
					// alan bayad khanye i om 3ta araye class bill yani tedad o foodcode o gheymat hashoon ro por konam
					L.foods_code[i] = foodcode;
					L.numbers[i] = tedad;
					L.prices[i] = O.Price;
					F.close();
				}
			}
			// } else
		}
		// } for
		types = i;
		cout << "\n_________________________________________________________\n";
		cout<<"||\trow\tName\tTedad\tPrice\t | Total Price ||";
		cout << "\n||_____________________________________________________||\n";
		F.open("Foods.mojy", ios::in | ios::binary);
		if (F.is_open() != true)
		{
			cout << "\aError Opening Foods File.";
		}
		else
		{
			for (i = 0; i < types; i++)
			{
				cout <<"||\t"<< i + 1 << "-\t";
				// peyda kardane esme ghaza az file ghazaha
				// mishod dakhel for araye 2 bodi begiram va esm haro berizam too oon va alan bejaye search az file az roo oon bekhunam
				// age vaght shod badan inkaro mikonm 4:06 AM 5/31/2018
				F.seekg(0, ios::beg);
				// neshangar file ro mizaram avvale file ta az avval shoro koone be khundan
				F.read((char *)&O, sizeof(Food));
				while (F.eof() != true)
				{
					if (O.Food_No == L.foods_code[i])
					{
						// yani ghaza ro peyda karde
						pos = F.tellg();
						pos -= sizeof(O);
						F.seekg(pos, ios::beg);
						cout << O.Name << "\t";
                        break;
					}
					F.read((char *)&O, sizeof(Food));
				}

				if (O.Food_No != L.foods_code[i])
				{
					// yani file ro ta akhar khoonde vali ghaza ro peyda nakarde
					cout << "\ano such food!!\t";
					// ya file ghaza moshkel darad khat balayi beja esm ghaza chap mishe
					// nemidunam break bezanam ya return ya chi
				}
				// alan esm chap shode hala baghie ro chap miknm

				cout << L.numbers[i] << "\t";
				cout << L.prices[i] << "\t |  ";
				cout << L.numbers[i] * L.prices[i]<<"\n";
				total_price += L.numbers[i] * L.prices[i];
			}
			// } for
			// alan list ghaza ha ro chap kard hala gheymat koll o max time
			F.close();
			cout << "=======================================================||";
			cout << "\nYour order maximum required time is: " << maxtime << " minutes";
			cout << "\nTotal price is:\t" << total_price<<"\n";
		}
		// faktor kamel chap shod
		cout << "\nEnter Y to order or N to cancel\t";
		cin.ignore();
		cin.get(a);
		if (a == 'Y' || a == 'y' || a=='1')
		{
		    do
            {
                cout << "\nEnter Account no (enter 0 to add new customer)\t";
                cin.ignore();
                cin >> L.Bill_Customer_No;
                if (L.Bill_Customer_No==0)
                    break;
                // in ye tikke kod ro mishe badan tabe kard va azash to chand jaa estefade kard
                F.open("Customers.mojy", ios::in | ios::binary);
                if (F.is_open() != true)
                {
                    cout << "\aError Opening customers File.";
                }
                else
                {
                    pos = (L.Bill_Customer_No - 1000) * sizeof(Customer);
                    if (pos >= file_size("Customers.mojy"))
                    {
                        cout << "\aNo such account";
                        F.close();
                    }
                    else
                    {
                        F.seekg(pos, ios::beg);
                        F.read((char *)&K, sizeof(Customer));
                        F.close();
                        break;
                    }
                }

			}
			while(L.Bill_Customer_No!=0);
			if(L.Bill_Customer_No==0)
            {
                // sabt moshtari jadid
                K.Open();
                E.open("Customers.mojy", ios::app | ios::binary);
                E.write((char *)&K, sizeof(K));
                L.Bill_Customer_No=K.Account_No;
                E.close();
            }
			// daryafte tarikh
			cout<<"\nnow enter date:\n";
			L.DOB_Bill_Open();
			// shomare soorat hesab ro dorost kn az 10000
			L.Bill_No = 10000 + file_size("Bills.mojy") / sizeof(Bill);
			// mishe gerafikish kard
			cout<<"\nYour Bill No is:\t"<<L.Bill_No<<"\nThanks for your choose\n";
			Sleep(100);
			// write to file Bill
			E.open("Bills.mojy", ios::app | ios::binary);
			E.write((char *)&L, sizeof(L));
			E.close();
			// berooz resani mojoodi dar file ghazaha
			Z.open("Foods.mojy", ios::in | ios::out | ios::binary);
				for (i = 0; i < types; i++)
				{
					Z.seekg(0, ios::beg);
					if (Z.is_open() != true)
					{
						cout << "\aError Opening Foods File.";
						break;
					}
					Z.read((char *)&O, sizeof(Food));
					while (Z.eof() != true)
					{
						if (O.Food_No == L.foods_code[i])
						{
							// Write to File Foods
							pos = Z.tellg();
							pos -= sizeof(O);
							O.Mojoodi -= L.numbers[i];
							Z.seekg(pos, ios::beg);
							Z.write((char *)&O, sizeof(O));
							break;
						}
						Z.read((char *)&O, sizeof(Food));
					}
					Z.seekg(pos, ios::beg);
					if (O.Food_No != L.foods_code[i])
					{
						cout << "\n\ano such food!!";
					}
				}
                // } for beroozresani
            Z.close();
		}
		// } if e sefaresh midi ya na bad az faktor
		return;
	}
	// } if e sefaresh midi ya na bad az namayesh e ghazaha
	else
    // gofte na
    return;
}

void Customers_Edit()
{
	Customer M,MD;
	ofstream A;
	ifstream B;
	fstream X;
	int Customers_Options, Acc;
	long int pos;
	do
	{
	    if (Check_Registry() == 0)
            cout << "\nto have more options please buy a full version\n";
		cout << "\n\t/ Customers Options \\  \n";
		cout << "\n|\t1) Add customer";
		cout << "\n|\t2) Delete Customer";
		cout << "\n|\t3) Edit Customer";
		cout << "\n|\t4) Search Customer";
		cout << "\n|\t5) Print Customers";
		cout << "\n|\t0) Exit";
		cout << "\n Enter your choice: ";
		cin >> Customers_Options;
		switch (Customers_Options)
		{
		case 1:
		    {
		     // Add customer
			M.Open();
            A.open("Customers.mojy", ios::app | ios::binary);
            A.write((char *)&M, sizeof(M));
            A.close();
			break;
		    }
		case 2:
		    {
		     // Delete Customer
			cout << "Enter customer account number to delete:\t";
			cin.ignore();
			cin >> Acc;
			X.open("Customers.mojy", ios::in | ios::out | ios::binary);
			if (X.is_open() != true)
			{
				cout << "\aError Opening Customers File.";
				return;
			}
			pos = (Acc - 1000) * sizeof(Customer);
			if (pos >= file_size("Customers.mojy"))
			{
				cout << "\aNo such account";
				return;
			}
			X.seekg(pos, ios::beg);
			X.read((char *)&MD, sizeof(Customer));
			MD.customer_flag=0;
			// Write to File
			X.seekg(pos, ios::beg);
			X.write((char *)&MD, sizeof(MD));
			X.close();
			cout<<"\nCustomer  "<<Acc<<"  successfully deleted\n";
            break;
		    }
		case 3:
		    {
		     // Edit Customer
			cout << "Enter customer account number to edit:\t";
			cin.ignore();
			cin >> Acc;
			X.open("Customers.mojy", ios::in | ios::out | ios::binary);
			if (X.is_open() != true)
			{
				cout << "\aError Opening Customers File.";
				return;
			}
			pos = (Acc - 1000) * sizeof(Customer);
			if (pos >= file_size("Customers.mojy"))
			{
				cout << "\aNo such account";
				return;
			}
			X.seekg(pos, ios::beg);
			X.read((char *)&M, sizeof(Customer));
			cout<<"\n\t"<<M<<"\n";
            M.Customer_Edit_Open();
			X.seekg(pos, ios::beg);
			X.write((char *)&M, sizeof(M));
			X.close();
			cout<<"\nCustomer  "<<Acc<<"  successfully edited\n";
			break;
		    }
		case 4:
		    {
		     // Search Customer
			cout << "Enter customer account number to find:\t";
			cin.ignore();
			cin >> Acc;
			B.open("Customers.mojy", ios::in | ios::binary);
			if (B.is_open() != true)
			{
				cout << "\aError Opening Customers File.";
				return;
			}
			pos = (Acc - 1000) * sizeof(Customer);
			if (pos >= file_size("Customers.mojy"))
			{
				cout << "\aNo such account";
				return;
			}
			B.seekg(pos, ios::beg);
			B.read((char *)&M, sizeof(Customer));
			cout<<"Name\t\tLast Name\t\tPhone\t\t\tAccount No\n";
			cout<<M;
			B.close();
			break;
		    }
        case 5:
            {
              // print account
            B.open("Customers.mojy", ios::in|ios::binary);
            if(B.is_open() != true)
            {
                cout<<"\aError Opening Customers File.";
            }
            else
            {
                B.read((char *)&M, sizeof(Customer));
                while(B.eof() != true)
                {
                    if(M.customer_flag==1)
                    {
                         cout<<M;
                    }
                    B.read((char *)&M, sizeof(Customer));
                }
            }
            B.close();
            break;
            }
		case 0:
			return ;
		default:
			cout << "\aWrong Choice";
		}
	}
	while (Customers_Options != 0);
	return;
}

void Foods_Edit()
{
	Food N,ND;
	edited_Food EN;
	ofstream C;
	ifstream D;
	fstream Y;
	int Foods_Options, foodcode;
	long int pos;
	do
	{
	    if (Check_Registry() == 0)
            cout << "\nto have more options please buy a full version\n";
        cout<<"\n\n/\t/ Foods Options \\\n";
		cout << "\n|\t1) Add Food";
		cout << "\n|\t2) Delete Food";
		cout << "\n|\t3) Edit Food";
		cout << "\n|\t4) Search Food";
		cout << "\n|\t5) Print Foods";
		cout << "\n|\t0) Exit";
		cout << "\n Enter your choice: ";
		cin >> Foods_Options;
		switch (Foods_Options)
		{
            case 1:
                {
                    // Add Food
                    N.Open();
                    C.open("Foods.mojy", ios::app | ios::binary);
                    C.write((char *)&N, sizeof(N));
                    C.close();
                    break;
                }
            case 2:
                {
                   // Delete Food
                    cout << "\nEnter food code to delete:\t";
                    cin.ignore();
                    cin >> foodcode;
                    Y.open("Foods.mojy", ios::in | ios::out | ios::binary);
                    if (Y.is_open() != true)
                    {
                        cout << "\aError Opening Foods File.";
                        break;
                    }
                    Y.read((char *)&ND, sizeof(Food));
                    while(Y.eof() != true)
                    {
                        if(ND.Food_No == foodcode)
                        {
                            ND.food_flag=0;
                            // Write to File
                            pos=Y.tellg();
                            pos -= sizeof(ND);
                            Y.seekg(pos,ios::beg);
                            Y.write((char *)&ND, sizeof(ND));
                            Y.close();
                            cout<<"\nFood  "<<foodcode<<"  successfully deleted\n";
                            break;
                        }
                        Y.read((char *)&ND, sizeof(Food));
                    }
                    Y.close();
                    break;
                }
			case 3:
                {
                    // Edit Food
                    cout << "\nEnter Food code to edit:\t";
                    cin.ignore();
                    cin >> foodcode;
                    Y.open("Foods.mojy", ios::in | ios::out | ios::binary);
                    if (Y.is_open() != true)
                    {
                        cout << "\nError Opening Foods File.";
                        break;
                    }
                    Y.read((char *)&N, sizeof(Food));
                    while(Y.eof() != true)
                    {
                        if(N.Food_No == foodcode)
                        {
                            cout<<N<<"\n";
                            // ghabl az inke taghir bedam mirizam too file e edited foods
                            EN.Food_No=N.Food_No;
                            strcpy(EN.Name,N.Name);
                            EN.Last_Bill_No = (10000-1)+ file_size("Bills.mojy")/ sizeof(Bill);
                            // EN.edited_times ro payin zdm
                            // Write to File har do file e edited foods va foods
                            pos=Y.tellg();
                            pos -= sizeof(N);
                            // check kardn shomare ghazaye tekrari ro badan minevisam
                            N.Food_Edit_Open(foodcode);
                            N.food_edit_flag++;
                            EN.edited_times=N.food_edit_flag;
                            Y.seekg(pos,ios::beg);
                            Y.write((char *)&N, sizeof(N));
                            // alan file foods ok shod , hala file e edited foods
                            C.open("Edited_Foods.mojy", ios::app | ios::binary);
                            C.write((char *)&EN, sizeof(EN));
                            C.close();
                            // file e edited foods ham kamel shod
                            cout<<"\nFood  "<<foodcode<<"  successfully edited\n";
                            foodcode=0;
                            break;
                        }
                        Y.read((char *)&N, sizeof(Food));
                    }
                    //Y.seekg(pos,ios::beg);
                    if(foodcode!=0)
                    {
                        cout<<"\n\ano such food\n";
                    }
                    Y.close();
                    break;
                }
            case 4:
                {
                  // Search Food
                    cout << "Enter Food code to find:\t";
                    cin.ignore();
                    cin >> foodcode;
                    D.open("Foods.mojy", ios::in | ios::binary);
                    if (D.is_open() != true)
                    {
                        cout << "\aError Opening Foods File.";
                        break;
                    }
                    D.read((char *)&N, sizeof(Food));
                    while(D.eof() != true)
                    {
                        if(N.Food_No == foodcode)
                        {
                            cout<<N<<"\n";
                            D.close();
                            break;
                        }
                    D.read((char *)&N, sizeof(Food));
                    }
                    D.close();
                    if(N.Food_No!=foodcode)
                    {
                        cout << "\n\ano such food";
                    }
                    break;
                }
            case 5:
                {
                  // print foods
                  // badan emkanate bishtar ezafe mishe
                    Print_Foods(1);
                    break;
                }
            case 0:
                return ;
            default:
                cout << "Wrong Choice";
		}
	}
	while (Foods_Options != 0);
}

void Reports()
{
    // shoroo miknim b neveshtn :) 6/1/2018 3:25 AM
    Bill BR;
	Food FR;
	edited_Food ER;
	ifstream BILLS,AB;
	ifstream FOODS;
	ifstream EF;
	Date FROM;
	Date TO;
	int i, Reports_Options, Total_Prices=0;
	int c=0;
	long int AR;
    do
    {
        if (Check_Registry() == 0)
            cout << "\nto have more options please buy a full version\n";
        cout<<"\n/\t/ Reports Options \\\n";
		cout << "\n|\t1) Print Bills in period of time";
		cout << "\n|\t2) Print Bill by customer account number";
        if (Check_Registry() == 1)
        {
            cout << "\n|\t3) Print Bill by bill number";
            cout << "\n|\t4) Find bills by food";
            cout << "\n|\t5) Print favorite foods";
            cout << "\n|\t6) Print each customer favorite foods";
        }
		cout << "\n|\t9) Print All Bills";
		cout << "\n|\t0) Exit";
		cout << "\nEnter your choice:\t";
		cin >> Reports_Options;
		switch (Reports_Options)
		{
        case 1:
        {
            // chap soorat hesab haa dar baze zamani moshakhas
            // avval file ro baz bokone age baz shod tarikh begire
            BILLS.open("Bills.mojy", ios::in | ios::binary);
            if (BILLS.is_open() != true)
            {
                cout << "\aNo Bill Saved";
                break;
            }
            // file baz shode hala tarikh haa ro begir
            // mishod too class date tabe open tarif kard amma nemidunma chera kar nemikard!
            cout<< "\nEnter beginning date:\n";
            cout << "Day:\t";
            cin >> FROM.Day;
            cout << "Month:\t";
            cin >> FROM.Month;
            cout << "Year:\t";
            cin >> FROM.Year;
            cout << "\nEnter ending date:\n";
            cout << "\nDay:\t";
            cin >> TO.Day;
            cout << "Month:\t";
            cin >> TO.Month;
            cout << "Year:\t";
            cin >> TO.Year;
            // dota tarikh ro gereftm
            // halghe khandan e bills va check kardn tarikh
            cout << "\n_________________________________________________________________________________________________\n";
            cout<<"||\trow\tName\tTedad\tPrice\t| Total Price ||   Bill No\tCustomer No\tDate   ||";
            cout << "\n||____________________________________________________||_______________________________________||\n";
            BILLS.read((char *)&BR, sizeof(Bill));
            while (BILLS.eof() != true)
            {
                if ((FROM.Year<=BR.DOB.Year && BR.DOB.Year<=TO.Year) && (FROM.Month <= BR.DOB.Month && BR.DOB.Month<= TO.Month) && (FROM.Day <= BR.DOB.Day && BR.DOB.Day<= TO.Day))
                {
                    // yani bills e peyda shode too baze bood
                    // halghe chap faktor
                    // avval file e asli ghazaha bad file ghazahaye edit shode
                    Total_Prices+=Print_Bill(BR,1,c);
                    cout <<"||----------------------------------------------------------"<< BR.Bill_No << "\t   ";
                    cout << BR.Bill_Customer_No << "\t      ";
                    cout << BR.DOB.Day << "/" << BR.DOB.Month << "/" << BR.DOB.Year<<"  \n";
                    cout<<"\n";
                }
                    // } if , mire soorat hesabe badi
                BILLS.read((char *)&BR, sizeof(Bill));
            }
            BILLS.close();
            cout << "||====================================================||=======================================||";
            cout<<"\nNumber of all the foods in period u entered is:\t"<<c;
            cout << "\nTotal prices is:\t\t\t" << Total_Prices <<"\n";
            c=0;
            Total_Prices=0;
            break;
        }
        case 2:
            {
                // chap soorat hesabhaye har moshtari
                BILLS.open("Bills.mojy", ios::in | ios::binary);
                if (BILLS.is_open() != true)
                {
                    cout << "No Bill Saved";
                    break;
                }
                cout<< "\nEnter Account No:\t";
                cin>>AR;
                cout << "\n_________________________________________________________________________________________________\n";
                cout<<"||\trow\tName\tTedad\tPrice\t| Total Price ||   Bill No\tCustomer No\tDate   ||";
                cout << "\n||____________________________________________________||_______________________________________||\n";
                BILLS.read((char *)&BR, sizeof(Bill));
                while (BILLS.eof() != true)
                {
                    if (BR.Bill_Customer_No==AR)
                    {
                        Total_Prices+=Print_Bill(BR,1,c);
                        cout <<"||----------------------------------------------------------"<< BR.Bill_No << "\t   ";
                        cout << BR.Bill_Customer_No << "\t      ";
                        cout << BR.DOB.Day << "/" << BR.DOB.Month << "/" << BR.DOB.Year<<"  \n";
                        cout<<"\n";
                    }
                    // } if
                    BILLS.read((char *)&BR, sizeof(Bill));
                }
                BILLS.close();
                cout << "||====================================================||=======================================||";
                cout<<"\nNumber of all the foods in period u entered is:\t"<<c;
                cout << "\nTotal prices is:\t\t\t" << Total_Prices <<"\n";
                c=0;
                Total_Prices=0;
                break;
            }
            case 3:
            {
                // chap soorat hesab ba shomare soorat hesab
                if(Check_Registry() == 0)
                    {
                        cout << "\aWrong Choice\n";
                        break;
                    }
                BILLS.open("Bills.mojy", ios::in | ios::binary);
                if (BILLS.is_open() != true)
                {
                    cout << "No Bill Saved";
                    break;
                }
                cout<< "\nEnter Bill No:\t";
                cin>>AR;
                cout << "\n_________________________________________________________________________________________________\n";
                cout<<"||\trow\tName\tTedad\tPrice\t| Total Price ||   Bill No\tCustomer No\tDate   ||";
                cout << "\n||____________________________________________________||_______________________________________||\n";
                BILLS.read((char *)&BR, sizeof(Bill));
                while (BILLS.eof() != true)
                {
                    if (BR.Bill_No==AR)
                    {
                        Total_Prices+=Print_Bill(BR,1,c);
                        cout <<"||----------------------------------------------------------"<< BR.Bill_No << "\t   ";
                        cout << BR.Bill_Customer_No << "\t      ";
                        cout << BR.DOB.Day << "/" << BR.DOB.Month << "/" << BR.DOB.Year<<"  \n";
                        cout<<"\n";
                    }
                    // } if
                    BILLS.read((char *)&BR, sizeof(Bill));
                }
                BILLS.close();
                cout << "||====================================================||=======================================||";
                cout << "\nTotal prices is:\t\t\t" << Total_Prices <<"\n";
                c=0;
                Total_Prices=0;
                break;

            }
            case 4:
            {
                // chap soorat hesabhayi k felan ghaza tooshe
                if(Check_Registry() == 0)
                    {
                        cout << "\aWrong Choice\n";
                        break;
                    }
                cout<<"\nThis option will be created in next version\n";
                break;
            }
            case 5:
            {
                // chap ghazahaye morede alaghe
                if(Check_Registry() == 0)
                    {
                        cout << "\aWrong Choice\n";
                        break;
                    }
                cout<<"\nThis option will be created in next version\n";
                break;
            }
            case 6:
            {
                // chap ghazahaye morede alaghe har moshtari
                if(Check_Registry() == 0)
                    {
                        cout << "\aWrong Choice\n";
                        break;
                    }
                cout<<"\nThis option will be created in next version\n";
                break;
            }
        case 9:
            {
                // print all bills
                AB.open("Bills.mojy" , ios::in | ios::binary);
                if (AB.is_open()!=true)
                {
                    cout<<"\nError Opening Bills File\n";
                    break;
                }
                cout << "\n_________________________________________________________________________________________________\n";
                cout<<"||\trow\tName\tTedad\tPrice\t| Total Price ||   Bill No\tCustomer No\tDate   ||";
                cout << "\n||____________________________________________________||_______________________________________||\n";
                AB.read((char *)&BR, sizeof(Bill));
                while(AB.eof() != true)
                {
                    Total_Prices+=Print_Bill(BR,1,c);
                    cout <<"||----------------------------------------------------------"<< BR.Bill_No << "\t   ";
                    cout << BR.Bill_Customer_No << "\t      ";
                    cout << BR.DOB.Day << "/" << BR.DOB.Month << "/" << BR.DOB.Year<<"  \n";
                    cout<<"\n";
                    AB.read((char *)&BR, sizeof(Bill));
                }
                AB.close();
                cout << "||====================================================||=======================================||";
                cout<<"\nNumber of all the foods:\t"<<c;
                cout << "\nTotal prices is:\t\t" << Total_Prices <<"\n";
                c=0;
                Total_Prices=0;
                break;
            }
        default:
        cout << "Wrong Choice";
		}
    }
    while(Reports_Options!=0);
        return;
}

void About()
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

	if (Check_Registry() == 0)
    {
		cout<< "\n\t\t\t    ";
		SetConsoleTextAttribute(h, 0xF0);
		cout<<"Demo Mode";
		SetConsoleTextAttribute(h, 0x07);
		cout<<"\n\t\t     ";
		SetConsoleTextAttribute(h, 0xF0);
		cout<<"please buy a full version\n";
    SetConsoleTextAttribute(h, 0x07);
    }
	else
    {
        SetConsoleTextAttribute(h, 0x07);
		cout<< "\n\t\t\t   ";
		SetConsoleTextAttribute(h, 0xF0);
		cout<<"Full Version";
        SetConsoleTextAttribute(h, 0x07);
		cout<<"\n\t\t   ";
		SetConsoleTextAttribute(h, 0xF0);
		cout<<"Thanks for buy a full version\n\n";
		SetConsoleTextAttribute(h, 0x07);
        cout<< "\n \t\t\t";
        SetConsoleTextAttribute(h, 0xF0);
        cout<<"Restaurant Project";
        SetConsoleTextAttribute(h, 0x07);
        cout<<"\n\t\t\t    ";
        SetConsoleTextAttribute(h, 0xFA);
        cout<<"Supervisor:";
        SetConsoleTextAttribute(h, 0x07);
	    cout<<"\n\t\t\t";
	    SetConsoleTextAttribute(h, 0xF0);
	    cout<<"Dr Mohammad Farshi";
	    SetConsoleTextAttribute(h, 0x07);
	    cout<<"\n\t\t\t   ";
	    SetConsoleTextAttribute(h, 0xFA);
	    cout<<"Developed by:";
	    SetConsoleTextAttribute(h, 0x07);
        cout<<"\n\t\t\t";
        SetConsoleTextAttribute(h, 0xF0);
        cout<<"Mojtaba Alehoseini";
        SetConsoleTextAttribute(h, 0x07);
        cout<<"\n\t\t\t     ";
        SetConsoleTextAttribute(h, 0xF3);
        cout<<"13/6/2018"; // 23/3/1397
        SetConsoleTextAttribute(h, 0x07);
        cout<<"\n\n";
    }
}

void Contact_me()
{
	cout << "\n\t Ways to contact with me:\n\n\t     Email:     alehoseini.mojtaba@gmail.com\n\t Phone Number:  +989120211520\n";
}

int main()
{
    Bill P;
	ofstream G;
	ifstream H;
	fstream I;
	long int poss;
	int Choice;
		do
		{
		    if (Check_Registry() == 0)
            {
                cout << "\n\t\t\t\t\t RESTAURANT *Demo Mode* ";
                cout<< "\n to have more option buy full version";
            }
            if (Check_Registry() == 1)
                cout << "\n\t\t\t\t\t RESTAURANT full version ";
			cout << "\n 1) Order";
			cout << "\n 2) Customers";
			cout << "\n 3) Foods";
			cout << "\n 4) Reports";
			if (Check_Registry() == 1)
            {
                cout << "\n 5) Discount Code";
                cout << "\n 6) Setting";
            }
            if (Check_Registry() == 0)
                cout << "\n 7) Register";
			cout << "\n 8) Contact with me";
			cout << "\n 9) About";
			cout << "\n 0) Exit";
			cout << "\nEnter your choice:";
			cin >> Choice;
			switch (Choice)
			{
			case 1:
				// order
                Order();
                break;
			case 2:
				// customers
                Customers_Edit();
                break;
			case 3:
				// foods
                Foods_Edit();
                break;
			case 4:
				// reports
				Reports();
				break;
			case 5:
                {
                    // discount code
                    if(Check_Registry() == 0)
                    {
                        cout << "\aWrong Choice\n";
                        break;
                    }
                    cout<<"\nThis option will be created in next version\n";
                    cout<<"in this option you can create discount code and use it in order\n";
                    break;
                }
            case 6:
                {
                   // setting --> password va rang
                   if(Check_Registry() == 0)
                    {
                        cout << "\aWrong Choice\n";
                        break;
                    }
                    cout<<"\nThis option will be created in next version\n";
                    cout<<"in this option you can create password and you can change color\n";
                    break;
                }
                case 7:
                // register
                if(Check_Registry() == 1)
                {
                    cout << "\aYou had registered before\n";
                    break;
                }
                Check_Key(0);
                break;
			case 8:
				// about
				Contact_me();
				break;
			case 9:
				// contact with me
				About();
				break;
			case 0:
				return 0;
			default:
				cout << "\aWrong Choice";
			}
		}
		while (Choice != 0);
	return 0;
}
//mojtaba96
