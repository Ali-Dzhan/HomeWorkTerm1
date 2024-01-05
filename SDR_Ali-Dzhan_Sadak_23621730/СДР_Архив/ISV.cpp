#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

// ��������� �� ����

struct Deposit {
    double value;
    int creationYear;
    char currency[20];
};

// ��������� �� ��������

struct Investor {
    int accountNumber;
    char name[30];
    Deposit deposits[3]; // ����� �� ���������
    int numDeposits; // ���� �������
    int openingYear;
};


// ������� �� �������� �� ���� �������� � �������

void addInvestor(Investor investors[], int& numInvestors) {

    Investor& newInvestor = investors[numInvestors];

    cout << "�������� ����� �� ������: ";
    cin >> newInvestor.accountNumber;

    cout << "�������� ���: ";
    cin.ignore();  // ������� �� ������
    cin.getline(newInvestor.name, 30); // getline �� c-string

    cout << "�������� ������ �� ��������� �� ��������: ";
    cin >> newInvestor.openingYear;

    do {
        cout << "�������� ���� ������� (�� 1 �� 3): ";
        cin >> newInvestor.numDeposits;

        if (newInvestor.numDeposits < 1 || newInvestor.numDeposits > 3) {
            cout << "����� �� ��������� ������ �� � ����� 1 � 3. ����, �������� ������.\n";
        }

    } while (newInvestor.numDeposits < 1 || newInvestor.numDeposits > 3);

    for (int i = 0; i < newInvestor.numDeposits; ++i) {
        while (true) {
            cout << "�������� ������ �� ����� " << i + 1 << " (BGN, USD, EURO): ";
            cin.ignore();
            cin.getline(newInvestor.deposits[i].currency, 20);

            if (strcmp(newInvestor.deposits[i].currency, "BGN") == 0 ||
                strcmp(newInvestor.deposits[i].currency, "USD") == 0 ||
                strcmp(newInvestor.deposits[i].currency, "EURO") == 0) {
                break; // ������ �� �� ������, ��� � ������� ��������
            }

            cout << "��������� ��������. �������� ������� ������.\n";
        }

        cout << "�������� �������� �� ����� " << i + 1 << ": ";
        cin >> newInvestor.deposits[i].value;

        cout << "�������� ������ �� ��������� �� ����� " << i + 1 << ": ";
        cin >> newInvestor.deposits[i].creationYear;
    }
        cout << "���������� ���� ������� �������.\n\n";

        numInvestors++;
}


// �������� �� ������ �� ���������

void addInvestorsList(Investor investors[], int& numInvestors) {
        
    int n;

    do {
        cout << "�������� ���� ���������: ";
        cin >> n;

        if (n > 50) {
            cout << "��������� � ������������ ���� ���������! ����, �������� ������.\n";
        }
        else if (n <= 0) {
            cout << "������! ����� �� ����������� ������ �� ���� ��-����� �� 0. ����, �������� ������.\n";
        }

    } while (n > 50 || n <= 0);

    for (int i = 0; i < n; ++i) {
        addInvestor(investors, numInvestors);
    }
}

// ����������� � ������� ���

void allInvestors(Investor investors[], int& numInvestors) {
    cout << "���������� �� ������ ���������:\n\n";
    cout << setw(10) << "����� �� ������" << setw(20) << "��� �� ��������" << setw(25) << "������ �� ���������" << "\n";
    cout << setw(62) << setfill('-') << "\n" << setfill(' ');

    for (int i = 0; i < numInvestors; ++i) {
        const Investor& currentInvestor = investors[i];
        cout << setw(4) << currentInvestor.accountNumber;
        cout << setw(23) << currentInvestor.name;
        cout << setw(22) << currentInvestor.openingYear << " �.\n\n";

        cout << "���������� �� �������: \n\n";

        for (int j = 0; j < currentInvestor.numDeposits; ++j) {
            const Deposit& currentDeposit = currentInvestor.deposits[j];
            cout << "  ������: " << currentDeposit.currency << "\n";
            cout << "  ��������: " << currentDeposit.value << " " << currentDeposit.currency << endl;
            cout << "  ������ �� ���������: " << currentDeposit.creationYear << "\n\n";
        }

        cout << setw(62) << setfill('-') << "\n" << setfill(' ');
    }

}

// ��������� � ���� � BGN

void investorsWithBGNDeposit(Investor investors[], int& numInvestors) {
    cout << "��������� � ���� � BGN:\n\n";
    cout << setw(10) << "����� �� ������" << setw(20) << "��� �� ��������" << setw(25) << "������ �� ���������" << "\n";
    cout << setw(62) << setfill('-') << "\n" << setfill(' ');

    for (int i = 0; i < numInvestors; ++i) {
        const Investor& currentInvestor = investors[i];

        // proverka dali depozita e v BGN
        bool hasBGNDeposit = false;
        for (int j = 0; j < currentInvestor.numDeposits; ++j) {
            if (strcmp(currentInvestor.deposits[j].currency, "BGN") == 0) {
                hasBGNDeposit = true;
                break;
            }
        }

        if (hasBGNDeposit) {
            cout << setw(4) << currentInvestor.accountNumber;
            cout << setw(23) << currentInvestor.name;
            cout << setw(22) << currentInvestor.openingYear << " �.\n";
        }
    }

    cout << setw(62) << setfill('-') << "\n" << setfill(' ');
}

// ��������� � ���������� ���� � EURO

void investorsWithMaxEURO(Investor investors[], int& numInvestors) {
    cout << "��������� � ���������� ���� � EURO:\n\n";
    cout << setw(10) << "����� �� ������" << setw(20) << "��� �� ��������" << setw(25) << "������ �� ���������" << setw(20) << "��������\n";
    cout << setw(92) << setfill('-') << "\n" << setfill(' ');

    // �������� �� ����������� ���� � EURO �� ����� ��������
    for (int i = 0; i < numInvestors; ++i) {
        const Investor& currentInvestor = investors[i];

        double maxDeposit = 0.0;

        // �������� �� ����������� ���� � EURO �� ������� ��������
        for (int j = 0; j < currentInvestor.numDeposits; ++j) {
            if (strcmp(currentInvestor.deposits[j].currency, "EURO") == 0 && currentInvestor.deposits[j].value > maxDeposit) {
                maxDeposit = currentInvestor.deposits[j].value;
            }
        }

        // ��������� �� ����������� � ������� ���-������ ����� � EURO
        if (maxDeposit > 0.0) {
            cout << setw(4) << currentInvestor.accountNumber;
            cout << setw(23) << currentInvestor.name;
            cout << setw(22) << currentInvestor.openingYear << " �.";
            cout << fixed << setprecision(2) << setw(20) << maxDeposit << " EURO" << endl;
        }
    }

    cout << setw(92) << setfill('-') << "\n" << setfill(' ');
}

// �� ��������� ��� �� ������ �� ������ // bubble sorting 

void rearrangeByAccNumber(Investor investors[], int& numInvestors) {
    bool swapped;

    for (int i = 0; i < numInvestors; i++) {
        swapped = false;

        for (int j = 0; j < numInvestors - i - 1; j++) {

            if (investors[j].accountNumber > investors[j + 1].accountNumber) {
                Investor temp = investors[j];
                investors[j] = investors[j + 1];
                investors[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

// ������� �� ������� ����� ����������� �� ������ ������ �� ��������� �� ������ � �� ������� �� ����� �� ������: 

void investorsByOpeningYearAndSort(Investor investors[], int& numInvestors) {
    int targetYear;
    cout << "�������� ������ �� ����������: ";
    cin >> targetYear;

    // ����� �� ����������� �� ��������� �� ������ ������
    Investor filteredInvestors[50];
    int numFilteredInvestors = 0;

    // ��������� �� ����������� �� �������� ������
    for (int i = 0; i < numInvestors; ++i) {
        if (investors[i].openingYear == targetYear) {
            filteredInvestors[numFilteredInvestors++] = investors[i];
        }
    }

    // ��������� �� ����� �� ������
    rearrangeByAccNumber(filteredInvestors, numFilteredInvestors);

    // ���������
    allInvestors(filteredInvestors, numFilteredInvestors);
}

// ������� �� ������� ����� �����������, ����� ���� ���� ���� ���� � �� ������� �� �������� �� ���� ����:

void investorsWithSingleDepositAndSort(Investor investors[], int& numInvestors) {
    cout << "��������� ��� ���� ���� ����, ��������� �� ��������:\n\n";
    cout << setw(10) << "����� �� ������" << setw(20) << "��� �� ��������" << setw(25) << "������ �� ���������" << setw(25) << "�������� �� ����\n";
    cout << setw(92) << setfill('-') << "\n" << setfill(' ');

    // bubble sort �� �������� �� �����
    bool swapped;
    for (int i = 0; i < numInvestors; ++i) {
        swapped = false;
        for (int j = 0; j < numInvestors - i - 1; ++j) {
            Deposit& deposit1 = investors[j].deposits[0];
            Deposit& deposit2 = investors[j + 1].deposits[0];

            if (deposit1.value > deposit2.value) {
                // swap � ������� ������, ��� ���������� � ��-������
                Investor temp = investors[j];
                investors[j] = investors[j + 1];
                investors[j + 1] = temp;
                swapped = true;
            }
        }

        // ��� ���� �������, ������� � ��������, �������� �� ������ ��������������
        if (!swapped) {
            break;
        }
    }

    // �������
    for (int i = 0; i < numInvestors; ++i) {
        Investor& currentInvestor = investors[i];

        // �������� ���� ��������� ��� 1 ����
        if (currentInvestor.numDeposits == 1) {
            Deposit& singleDeposit = currentInvestor.deposits[0];

            cout << setw(4) << currentInvestor.accountNumber;
            cout << setw(23) << currentInvestor.name;
            cout << setw(22) << currentInvestor.openingYear << " �.";
            cout << fixed << setprecision(2) << setw(20) << singleDeposit.value << " " << singleDeposit.currency << endl;
        }
    }

    cout << setw(92) << setfill('-') << "\n" << setfill(' ');
}

// �������� �� ���� �� �������� � ��-����� �� 3 ����� (���������� ��� ������� �� �� ���� �������)

void addNewDeposit(Investor& investor) {
    double newValue;
    int newYear;
    char newCurrency[20];

    if (investor.numDeposits >= 3) {
        cout << "���������� ���� ��� 3 ����� � �� ���� �� ������ ������.\n";
        return;
    }

    bool hasSameCurrency = false;
   
    // �������� ���� ���������� ���� ��� ���� � ���� ������
    while (true) {
        cout << "�������� ������ �� ����� ���� (BGN, USD, EURO): ";
        cin.ignore();
        cin.getline(newCurrency, 20);

        // �������� ���� ���������� ���� ��� ���� � ���� ������
        for (int i = 0; i < investor.numDeposits; i++) {
            if (strcmp(investor.deposits[i].currency, newCurrency) == 0) {
                cout << "���������� ��� ���� � ���� ������. ";
                hasSameCurrency = true;
                break;
            }
        }

        if (!hasSameCurrency) {
            break;
        }
        hasSameCurrency = false;

        cout << "����, �������� �������� ������.\n";
    }


    do {
        cout << "�������� �������� �� ����� ����: ";
        cin >> newValue;

        // ��������� �� ����������
        if (newValue >= 500) {
            break;
        }

        cout << "���������� �� ����� ���� ������ �� ���� ���� 500.\n";
    } while (true);

    cout << "�������� ������ �� ��������� �� �����: ";
    cin >> newYear;

    Deposit newDeposit;
    strcpy_s(newDeposit.currency, newCurrency);
    newDeposit.value = newValue;
    newDeposit.creationYear = newYear;

    // ������ �� ����� ���� � ������
    investor.deposits[investor.numDeposits++] = newDeposit;

    cout << "������ ���� ���� ������� �������.\n";
}

void addNewDepositForAccountNumber(Investor investors[], int numInvestors) {
    while (true) {
        cout << "�������� ����� �� ������, �� ����� �� �� ������ ��� ����: ";
        int accNumber;
        cin >> accNumber;

        bool found = false;

        for (int i = 0; i < numInvestors; ++i) {
            if (investors[i].accountNumber == accNumber) {
                addNewDeposit(investors[i]);
                found = true;
                break;
            }
        }

        if (found) {
            // ��� � �������, ����� �� ������
            break;
        }
        else {
            cout << "������������ �������� � ����� �����. ����, �������� ������.\n\n";
            // ���������� �� ������� 
            cin.clear();
            cin.ignore();
        }
    }
}

// ������� � �������

void submenuByAccNumber(Investor investors[], int& numInvestors) {
    int subChoice;

    do {
        cout << "\n������� 6\n";
        cout << "1. - ������ ����������� �� ��������� ��� �� ������ �� ��������\n";
        cout << "2. - ����������� �� ������ ������ �� ��������� �� ������\n";
        cout << "3. - �����������, ����� ���� ���� ���� ����\n";
        cout << "4. - ������� ��� ��������� ����\n";

        cin >> subChoice;

        if (subChoice > 4 && subChoice < 1) {
            cout << "�������� ���� ����� �� 1 �� 4.\n\n";
        }

        switch (subChoice) {
        case 1:
            rearrangeByAccNumber(investors, numInvestors);
            allInvestors(investors, numInvestors);
            break;
        case 2:
            // ������� �� ������� ����� ����������� �� ������ ������ �� ��������� �� ������ � �� ������� �� ����� �� ������: 
            investorsByOpeningYearAndSort(investors, numInvestors);
            break;
        case 3:
            // ������� �� ������� ����� �����������, ����� ���� ���� ���� ���� � �� ������� �� �������� �� ���� ����:
            investorsWithSingleDepositAndSort(investors, numInvestors);
            break;
        case 4:
            cout << "������� ��� ��������� ����.\n";
            break;
        }
    } while (subChoice != 4);
}

// ��������� �� ����

void depositWithdrawl(Investor investors[], int& numInvestors) {

    while (true) {

        cout << "�������� ����� �� ������, �� ����� �� �� ������� ����: ";
        int accNumber;
        cin >> accNumber;

        bool found = false;

        for (int i = 0; i < numInvestors; ++i) {
            if (investors[i].accountNumber == accNumber) {
                cout << "���������� �� ���������:\n";
                cout << "��� �� ��������: " << investors[i].name << endl;
                cout << "�������:\n";

                for (int j = 0; j < investors[i].numDeposits; ++j) {
                    const Deposit& currentDeposit = investors[i].deposits[j];
                    cout << "  " << j + 1 << ". ������: " << currentDeposit.currency << "\n";
                    cout << "     ��������: " << currentDeposit.value << " " << currentDeposit.currency << endl;
                }

                cout << "�������� ����� �� �����, �� ����� �� �� ������� ������: ";
                int selectedDeposit;
                cin >> selectedDeposit;

                if (selectedDeposit >= 1 && selectedDeposit <= investors[i].numDeposits) {
                    selectedDeposit--; // �������� �� � ������� ������

                    cout << "�������� ���� �� ���������: ";
                    double withdrawalAmount;
                    cin >> withdrawalAmount;

                    if (withdrawalAmount > 0 && withdrawalAmount <= investors[i].deposits[selectedDeposit].value) {
                        // ��������� �� ������
                        investors[i].deposits[selectedDeposit].value -= withdrawalAmount;
                        cout << "������ �� ����� � ������� ���������.\n";
                        if (investors[i].deposits[selectedDeposit].value == 0) {
                            cout << "��������� � ������ ����. ���� ������� �������� �� �������" << endl;

                        }
                    }
                    else {
                        cout << "������! ���������� ���� �� ��������� � ��-������ �� ��������� � ��������.\n";
                    }
                }
                else {
                    cout << "��������� ����� �� ����. ����, �������� ������.\n";
                }

                found = true;
                break;
            }
        }

        if (found) {
            // ��� � �������, ����� �� ������
            break;
        }
        else {
            cout << "������������ �������� � ����� �����. ����, �������� ������.\n\n";
            // ���������� �� �������
            cin.clear();
            cin.ignore();
        }
    }

}

// ��������� �� ������

int findIndexOfInvestor(Investor investors[], int& numInvestors,int& accNumber) {
    // ������� �� ���� ������ � ���� �� ������ ������������ � �������� �� �������� 
    // �� ����� ������� �� ����������� ��� ����������� ������
    for (int i = 0; i < numInvestors; i++) {
        if (investors[i].accountNumber == accNumber) {
            return i;
        }
    }
    return -1;
}
void closeInvestorProfile(Investor investors[], int& numInvestors) {
    // ���������� �� ������ �� ���������� �� ������ 
    if (numInvestors <= 0) {
        cout << "���� �������� ���������.\n\n";
    }
    else {
        cout << "�������� ����� �� ������, ����� ������ �� �� �������: ";
        int accNumber;
        cin >> accNumber;

        int investorIndexToRemove = findIndexOfInvestor(investors, numInvestors, accNumber);
        if (investorIndexToRemove != -1) {
            cout << "�������� �� ��������� " << investors[investorIndexToRemove].name
                << " � ����� �� ������ " << accNumber << " � ��������.\n";

            for (int i = investorIndexToRemove; i < numInvestors - 1; ++i) {
                investors[i] = investors[i + 1];
            }
            --numInvestors;
        }
        else {
            cout << "������������ �������� � ����� �����. ����, �������� ������.\n\n";
            // ���������� �� �������
            cin.clear();
            cin.ignore();
        }
    }
}

// ��������� �� ������ � ����� ��� ����(�������)

void BinaryOutputInvestors(Investor investors[], int& numInvestors, const string& filename) {
    ofstream file(filename, ios::binary);

    if (file.is_open()) {
        file.write((const char*)(&numInvestors), sizeof(numInvestors));

        for (int i = 0; i < numInvestors; ++i) {
            file.write((const char*)(&investors[i]), sizeof(Investor));
        }

        cout << "������������ ���� �������� � ������� ����.\n";
        file.close();
    }
    else {
        cout << "������ �� ���� �� ���� ������� ��� ���� ����������.\n";
    }
}

// ��������� �� ������ � ����� �� ����(�������)

void BinaryInputInvestors(Investor investors[], int& numInvestors, const string& filename) {
    ifstream file(filename, ios::binary);

    if (file.is_open()) {
        file.read((char*)&numInvestors, sizeof(numInvestors));

        for (int i = 0; i < numInvestors; ++i) {
            file.read((char*)&investors[i], sizeof(Investor));
        }

        cout << "������������ ���� ��������� �� �����.\n";
        file.close();
    }
    else {
        cout << "������ �� ���� �� ���� �������.\n";
    }
}

// ������� � ���������� �� �� ����� �� ���� (�������).

int loadInvestorsFromFile(const char fileName[], Investor investors[], int& numInvestors)
{
    ifstream file(fileName);

    if (!file)
    {
        cout << endl << "������ �� ���� �� ���� �������!";
        return -1;
    }

    int i = 0;
    while (!file.eof())
    {
        file >> investors[i].accountNumber;
        file.ignore();
        file.getline(investors[i].name, sizeof(investors[i].name));
        file >> investors[i].openingYear;
        file >> investors[i].numDeposits;
       
        for (int j = 0; j < investors[i].numDeposits; ++j)
        {
            file.ignore();
            file.getline(investors[i].deposits[j].currency, sizeof(investors[i].deposits[j].currency));
            file >> investors[i].deposits[j].value;
            file >> investors[i].deposits[j].creationYear;
        }

        i++;
    }
    file.close();

    cout << "������";

    return 0;
}


// ������� � ���������� �� �� ���������� ��� ���� (�������).

int saveInvestorsToFile(const char fileName[], Investor investors[], int& numInvestors)
{
    ofstream file(fileName, ios::app); /*������� � ���������� �� ����� �� �� �������� ��� ����(��������) ����� ��� ����������� �� ����������.*/

    if (!file)
    {
        cout << endl << "������ �� ���� �� ���� �������!";
        return -1;
    }

    for (int i = 0; i < numInvestors; ++i)
    {
        file << investors[i].accountNumber << '\n';
        file << investors[i].name << '\n';
        file << investors[i].openingYear << '\n';
        file << investors[i].numDeposits << '\n';

        for (int j = 0; j < investors[i].numDeposits; ++j)
        {
            file << investors[i].deposits[j].currency << '\n';
            file << investors[i].deposits[j].value << '\n';
            file << investors[i].deposits[j].creationYear << '\n';
        }

        file << investors[i].openingYear << '\n';
    }
    file.close();

    cout << "������";

    return 0;
}

// ���� ������� � ����

int main() {

    setlocale(LC_ALL, "Bulgarian");

    const string binaryFileName = "binary_file.dat";
    
    Investor investors[50];
    int numInvestors = 0;

    int choice;

    do {
        cout << "\n         ����\n";
        cout << "1. ������ ��� ��������\n";
        cout << "2. ������ ������ �� ���������\n";
        cout << "3. ������ ������ ���������\n";
        cout << "4. ������ ������� � BGN ����\n";
        cout << "5. ������ ������� � ���������� ���� � EURO\n";
        cout << "6. ������� �� ��������� � ��� ����\n";
        cout << "7. �������� �� ���� �� ��������� � ��-����� �� 3 �����\n";
        cout << "8. ��������� �� ���� �� ����, �� ����� �� ������\n";
        cout << "9. ��������� �� ������ ������\n";
        cout << "10. ������� �� ����/����� � ������� �������\n";
        cout << "11. ������� �� ����/����� � �������� �������\n";
        cout << "12. �����\n";
        cout << "�������� �����: ";
        cin >> choice;

        if (choice > 12 && choice < 1) {
            cout << "�������� ���� ����� �� 1 �� 12.\n\n";
        }

        switch (choice) {
        case 1:
            addInvestor(investors, numInvestors);
            break;
        case 2:
            addInvestorsList(investors, numInvestors);
            break;
        case 3:
            allInvestors(investors, numInvestors);
            break;
        case 4:
            investorsWithBGNDeposit(investors, numInvestors);
            break;
        case 5:
            investorsWithMaxEURO(investors, numInvestors);
            break;
        case 6:
            // �������
            submenuByAccNumber(investors, numInvestors);
            break;
        case 7:
            addNewDepositForAccountNumber(investors, numInvestors);
            break;
        case 8:
            depositWithdrawl(investors, numInvestors);
            break;
        case 9:
            closeInvestorProfile(investors, numInvestors);
            break;
        case 10: {
            int submenuChoice;

            do {
                cout << "\n��� ����\n";
                cout << "1. ��������� �� ������ � ����� �� ����(�������)\n";
                cout << "2. ��������� �� ������ � ����� ��� ����(�������)\n";
                cout << "3. ������� ��� ��������� ����\n";
                cout << "�������� �����: ";

                cin >> submenuChoice;

                if (submenuChoice > 3 && submenuChoice < 1) {
                    cout << "�������� ���� ����� �� 1 �� 3.\n\n";
                }

                switch (submenuChoice) {

                case 1:
                    BinaryInputInvestors(investors, numInvestors, binaryFileName);
                    break;
                case 2:
                    BinaryOutputInvestors(investors, numInvestors, binaryFileName);
                    break;
                case 3:
                    cout << "������� ��� ��������� ����.\n";
                    break;
                }
            } while (submenuChoice != 3);

            break;
        }
        case 11: {
            int submenuChoice;

            do {
                cout << "\n��� ����\n";
                cout << "1. ��������� �� ������ � ����� �� ����(�������)\n";
                cout << "2. ��������� �� ������ � ����� ��� ����(�������)\n";
                cout << "3. ������� ��� ��������� ����\n";
                cout << "�������� �����: ";

                cin >> submenuChoice;

                if (submenuChoice > 3 && submenuChoice < 1) {
                    cout << "�������� ���� ����� �� 1 �� 3.\n\n";
                }

                switch (submenuChoice) {

                case 1:
                    loadInvestorsFromFile("info.txt", investors, numInvestors);
                    break;
                case 2:
                    saveInvestorsToFile("info.txt", investors, numInvestors);
                    break;
                case 3:
                    cout << "������� ��� ��������� ����.\n";
                    break;
                }
            } while (submenuChoice != 3);

            break;
        }
        case 12:
            cout << "�������� �� ����������.\n";
            return 0;
        }

    } while (choice != 12);

    return 0;
}
