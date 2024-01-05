#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

// Структура за влог

struct Deposit {
    double value;
    int creationYear;
    char currency[20];
};

// Структура за вложител

struct Investor {
    int accountNumber;
    char name[30];
    Deposit deposits[3]; // масив от структура
    int numDeposits; // брой влогове
    int openingYear;
};


// Функция за добавяне на един вложител с влогове

void addInvestor(Investor investors[], int& numInvestors) {

    Investor& newInvestor = investors[numInvestors];

    cout << "Въведете номер на сметка: ";
    cin >> newInvestor.accountNumber;

    cout << "Въведете име: ";
    cin.ignore();  // чистене на потока
    cin.getline(newInvestor.name, 30); // getline за c-string

    cout << "Въведете година на откриване на сметката: ";
    cin >> newInvestor.openingYear;

    do {
        cout << "Въведете брой влогове (от 1 до 3): ";
        cin >> newInvestor.numDeposits;

        if (newInvestor.numDeposits < 1 || newInvestor.numDeposits > 3) {
            cout << "Броят на влоговете трябва да е между 1 и 3. Моля, въведете отново.\n";
        }

    } while (newInvestor.numDeposits < 1 || newInvestor.numDeposits > 3);

    for (int i = 0; i < newInvestor.numDeposits; ++i) {
        while (true) {
            cout << "Въведете валута на влога " << i + 1 << " (BGN, USD, EURO): ";
            cin.ignore();
            cin.getline(newInvestor.deposits[i].currency, 20);

            if (strcmp(newInvestor.deposits[i].currency, "BGN") == 0 ||
                strcmp(newInvestor.deposits[i].currency, "USD") == 0 ||
                strcmp(newInvestor.deposits[i].currency, "EURO") == 0) {
                break; // излиза се от цикъла, ако е валидна валутата
            }

            cout << "Невалидна стойност. Въведете валидна валута.\n";
        }

        cout << "Въведете стойност на влога " << i + 1 << ": ";
        cin >> newInvestor.deposits[i].value;

        cout << "Въведете година на създаване на влога " << i + 1 << ": ";
        cin >> newInvestor.deposits[i].creationYear;
    }
        cout << "Вложителят беше успешно добавен.\n\n";

        numInvestors++;
}


// Добавяне на списък от вложители

void addInvestorsList(Investor investors[], int& numInvestors) {
        
    int n;

    do {
        cout << "Въведете брой вложители: ";
        cin >> n;

        if (n > 50) {
            cout << "Достигнат е максималният брой вложители! Моля, въведете отново.\n";
        }
        else if (n <= 0) {
            cout << "Грешка! Броят на вложителите трябва да бъде по-голям от 0. Моля, въведете отново.\n";
        }

    } while (n > 50 || n <= 0);

    for (int i = 0; i < n; ++i) {
        addInvestor(investors, numInvestors);
    }
}

// Илюлстарция в оформен вид

void allInvestors(Investor investors[], int& numInvestors) {
    cout << "Информация за всички вложители:\n\n";
    cout << setw(10) << "Номер на сметка" << setw(20) << "Име на вложител" << setw(25) << "Година на откриване" << "\n";
    cout << setw(62) << setfill('-') << "\n" << setfill(' ');

    for (int i = 0; i < numInvestors; ++i) {
        const Investor& currentInvestor = investors[i];
        cout << setw(4) << currentInvestor.accountNumber;
        cout << setw(23) << currentInvestor.name;
        cout << setw(22) << currentInvestor.openingYear << " г.\n\n";

        cout << "Информация за влогове: \n\n";

        for (int j = 0; j < currentInvestor.numDeposits; ++j) {
            const Deposit& currentDeposit = currentInvestor.deposits[j];
            cout << "  Валута: " << currentDeposit.currency << "\n";
            cout << "  Стойност: " << currentDeposit.value << " " << currentDeposit.currency << endl;
            cout << "  Година на създаване: " << currentDeposit.creationYear << "\n\n";
        }

        cout << setw(62) << setfill('-') << "\n" << setfill(' ');
    }

}

// Вложители с влог в BGN

void investorsWithBGNDeposit(Investor investors[], int& numInvestors) {
    cout << "Вложители с влог в BGN:\n\n";
    cout << setw(10) << "Номер на сметка" << setw(20) << "Име на вложител" << setw(25) << "Година на откриване" << "\n";
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
            cout << setw(22) << currentInvestor.openingYear << " г.\n";
        }
    }

    cout << setw(62) << setfill('-') << "\n" << setfill(' ');
}

// Вложители с максимален влог в EURO

void investorsWithMaxEURO(Investor investors[], int& numInvestors) {
    cout << "Вложители с максимален влог в EURO:\n\n";
    cout << setw(10) << "Номер на сметка" << setw(20) << "Име на вложител" << setw(25) << "Година на откриване" << setw(20) << "Стойност\n";
    cout << setw(92) << setfill('-') << "\n" << setfill(' ');

    // Намиране на максималния влог в EURO за всеки вложител
    for (int i = 0; i < numInvestors; ++i) {
        const Investor& currentInvestor = investors[i];

        double maxDeposit = 0.0;

        // Намиране на максималния влог в EURO за текущия вложител
        for (int j = 0; j < currentInvestor.numDeposits; ++j) {
            if (strcmp(currentInvestor.deposits[j].currency, "EURO") == 0 && currentInvestor.deposits[j].value > maxDeposit) {
                maxDeposit = currentInvestor.deposits[j].value;
            }
        }

        // Извеждане на вложителите с техните най-големи влози в EURO
        if (maxDeposit > 0.0) {
            cout << setw(4) << currentInvestor.accountNumber;
            cout << setw(23) << currentInvestor.name;
            cout << setw(22) << currentInvestor.openingYear << " г.";
            cout << fixed << setprecision(2) << setw(20) << maxDeposit << " EURO" << endl;
        }
    }

    cout << setw(92) << setfill('-') << "\n" << setfill(' ');
}

// По нарастващ ред на номера на сметка // bubble sorting 

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

// Извлича от базовия масив вложителите от дадена година на откриване на сметка и ги сортира по номер на сметка: 

void investorsByOpeningYearAndSort(Investor investors[], int& numInvestors) {
    int targetYear;
    cout << "Въведете година за филтриране: ";
    cin >> targetYear;

    // масив за съхраняване на вложители от дадена година
    Investor filteredInvestors[50];
    int numFilteredInvestors = 0;

    // извличане на вложителите от дадената година
    for (int i = 0; i < numInvestors; ++i) {
        if (investors[i].openingYear == targetYear) {
            filteredInvestors[numFilteredInvestors++] = investors[i];
        }
    }

    // сортиране по номер на сметка
    rearrangeByAccNumber(filteredInvestors, numFilteredInvestors);

    // извеждане
    allInvestors(filteredInvestors, numFilteredInvestors);
}

// Извлича от базовия масив вложителите, които имат само един влог и ги сортира по стойност на този влог:

void investorsWithSingleDepositAndSort(Investor investors[], int& numInvestors) {
    cout << "Вложители със само един влог, сортирани по стойност:\n\n";
    cout << setw(10) << "Номер на сметка" << setw(20) << "Име на вложител" << setw(25) << "Година на откриване" << setw(25) << "Стойност на влог\n";
    cout << setw(92) << setfill('-') << "\n" << setfill(' ');

    // bubble sort по стойност на влога
    bool swapped;
    for (int i = 0; i < numInvestors; ++i) {
        swapped = false;
        for (int j = 0; j < numInvestors - i - 1; ++j) {
            Deposit& deposit1 = investors[j].deposits[0];
            Deposit& deposit2 = investors[j + 1].deposits[0];

            if (deposit1.value > deposit2.value) {
                // swap с буферна клетка, ако стойността е по-висока
                Investor temp = investors[j];
                investors[j] = investors[j + 1];
                investors[j + 1] = temp;
                swapped = true;
            }
        }

        // ако няма размяна, масивът е сортиран, излизане от цикъла преждевременно
        if (!swapped) {
            break;
        }
    }

    // дисплей
    for (int i = 0; i < numInvestors; ++i) {
        Investor& currentInvestor = investors[i];

        // проверка дали вложителя има 1 влог
        if (currentInvestor.numDeposits == 1) {
            Deposit& singleDeposit = currentInvestor.deposits[0];

            cout << setw(4) << currentInvestor.accountNumber;
            cout << setw(23) << currentInvestor.name;
            cout << setw(22) << currentInvestor.openingYear << " г.";
            cout << fixed << setprecision(2) << setw(20) << singleDeposit.value << " " << singleDeposit.currency << endl;
        }
    }

    cout << setw(92) << setfill('-') << "\n" << setfill(' ');
}

// Добавяне на влог за вложител с по-малко от 3 влога (следващите две функции са по това условие)

void addNewDeposit(Investor& investor) {
    double newValue;
    int newYear;
    char newCurrency[20];

    if (investor.numDeposits >= 3) {
        cout << "Вложителят вече има 3 влога и не може да добави повече.\n";
        return;
    }

    bool hasSameCurrency = false;
   
    // Проверка дали вложителят вече има влог с тази валута
    while (true) {
        cout << "Въведете валута на новия влог (BGN, USD, EURO): ";
        cin.ignore();
        cin.getline(newCurrency, 20);

        // Проверка дали вложителят вече има влог с тази валута
        for (int i = 0; i < investor.numDeposits; i++) {
            if (strcmp(investor.deposits[i].currency, newCurrency) == 0) {
                cout << "Вложителят има влог с тази валута. ";
                hasSameCurrency = true;
                break;
            }
        }

        if (!hasSameCurrency) {
            break;
        }
        hasSameCurrency = false;

        cout << "Моля, въведете различна валута.\n";
    }


    do {
        cout << "Въведете стойност на новия влог: ";
        cin >> newValue;

        // Валидация за стойността
        if (newValue >= 500) {
            break;
        }

        cout << "Стойността на новия влог трябва да бъде поне 500.\n";
    } while (true);

    cout << "Въведете година на създаване на влога: ";
    cin >> newYear;

    Deposit newDeposit;
    strcpy_s(newDeposit.currency, newCurrency);
    newDeposit.value = newValue;
    newDeposit.creationYear = newYear;

    // Добавя се новия влог в масива
    investor.deposits[investor.numDeposits++] = newDeposit;

    cout << "Новият влог беше успешно добавен.\n";
}

void addNewDepositForAccountNumber(Investor investors[], int numInvestors) {
    while (true) {
        cout << "Въведете номер на сметка, за която да се добави нов влог: ";
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
            // ако е намерен, изход от цикъла
            break;
        }
        else {
            cout << "Несъществува вложител с такъв номер. Моля, опитайте отново.\n\n";
            // изчистване на стрийма 
            cin.clear();
            cin.ignore();
        }
    }
}

// Справки с подменю

void submenuByAccNumber(Investor investors[], int& numInvestors) {
    int subChoice;

    do {
        cout << "\nПодменю 6\n";
        cout << "1. - Изведи вложителите по нарастващ ред на номера на сметката\n";
        cout << "2. - Вложителите от дадена година на откриване на сметка\n";
        cout << "3. - Вложителите, които имат само един влог\n";
        cout << "4. - Връщане към основното меню\n";

        cin >> subChoice;

        if (subChoice > 4 && subChoice < 1) {
            cout << "Изберете цяло число от 1 до 4.\n\n";
        }

        switch (subChoice) {
        case 1:
            rearrangeByAccNumber(investors, numInvestors);
            allInvestors(investors, numInvestors);
            break;
        case 2:
            // Извлича от базовия масив вложителите от дадена година на откриване на сметка и ги сортира по номер на сметка: 
            investorsByOpeningYearAndSort(investors, numInvestors);
            break;
        case 3:
            // Извлича от базовия масив вложителите, които имат само един влог и ги сортира по стойност на този влог:
            investorsWithSingleDepositAndSort(investors, numInvestors);
            break;
        case 4:
            cout << "Връщане към основното меню.\n";
            break;
        }
    } while (subChoice != 4);
}

// Изтегляне на влог

void depositWithdrawl(Investor investors[], int& numInvestors) {

    while (true) {

        cout << "Въведете номер на сметка, от която да се изтегли влог: ";
        int accNumber;
        cin >> accNumber;

        bool found = false;

        for (int i = 0; i < numInvestors; ++i) {
            if (investors[i].accountNumber == accNumber) {
                cout << "Информация за вложителя:\n";
                cout << "Име на вложител: " << investors[i].name << endl;
                cout << "Влогове:\n";

                for (int j = 0; j < investors[i].numDeposits; ++j) {
                    const Deposit& currentDeposit = investors[i].deposits[j];
                    cout << "  " << j + 1 << ". Валута: " << currentDeposit.currency << "\n";
                    cout << "     Стойност: " << currentDeposit.value << " " << currentDeposit.currency << endl;
                }

                cout << "Изберете номер на влога, от който ще се изтегли сумата: ";
                int selectedDeposit;
                cin >> selectedDeposit;

                if (selectedDeposit >= 1 && selectedDeposit <= investors[i].numDeposits) {
                    selectedDeposit--; // Превръща се в масивен индекс

                    cout << "Въведете сума за изтегляне: ";
                    double withdrawalAmount;
                    cin >> withdrawalAmount;

                    if (withdrawalAmount > 0 && withdrawalAmount <= investors[i].deposits[selectedDeposit].value) {
                        // Изтегляне на сумата
                        investors[i].deposits[selectedDeposit].value -= withdrawalAmount;
                        cout << "Сумата от влога е успешно изтеглена.\n";
                        if (investors[i].deposits[selectedDeposit].value == 0) {
                            cout << "Изтеглена е цялата сума. Няма налична стойност за теглене" << endl;

                        }
                    }
                    else {
                        cout << "Грешка! Въведената сума за изтегляне е по-голяма от наличната в сметката.\n";
                    }
                }
                else {
                    cout << "Невалиден номер на влог. Моля, опитайте отново.\n";
                }

                found = true;
                break;
            }
        }

        if (found) {
            // ако е намерен, изход от цикъла
            break;
        }
        else {
            cout << "Несъществува вложител с такъв номер. Моля, опитайте отново.\n\n";
            // изчистване на стрийма
            cin.clear();
            cin.ignore();
        }
    }

}

// Затваряне на профил

int findIndexOfInvestor(Investor investors[], int& numInvestors,int& accNumber) {
    // итерира се през масива и като се открие съответствие в номерата на сметките 
    // се връща индекса на инвеститора със съответната сметка
    for (int i = 0; i < numInvestors; i++) {
        if (investors[i].accountNumber == accNumber) {
            return i;
        }
    }
    return -1;
}
void closeInvestorProfile(Investor investors[], int& numInvestors) {
    // премахване на профил на инвеститор от масива 
    if (numInvestors <= 0) {
        cout << "Няма добавени вложители.\n\n";
    }
    else {
        cout << "Въведете номер на сметка, чийто профил да се затвори: ";
        int accNumber;
        cin >> accNumber;

        int investorIndexToRemove = findIndexOfInvestor(investors, numInvestors, accNumber);
        if (investorIndexToRemove != -1) {
            cout << "Профилът на вложителя " << investors[investorIndexToRemove].name
                << " с номер на сметка " << accNumber << " е затворен.\n";

            for (int i = investorIndexToRemove; i < numInvestors - 1; ++i) {
                investors[i] = investors[i + 1];
            }
            --numInvestors;
        }
        else {
            cout << "Несъществува вложител с такъв номер. Моля, опитайте отново.\n\n";
            // Изчистване на стрийма
            cin.clear();
            cin.ignore();
        }
    }
}

// Извеждане на масива с книги във файл(двоичен)

void BinaryOutputInvestors(Investor investors[], int& numInvestors, const string& filename) {
    ofstream file(filename, ios::binary);

    if (file.is_open()) {
        file.write((const char*)(&numInvestors), sizeof(numInvestors));

        for (int i = 0; i < numInvestors; ++i) {
            file.write((const char*)(&investors[i]), sizeof(Investor));
        }

        cout << "Информацията беше записана в двоичен файл.\n";
        file.close();
    }
    else {
        cout << "Файлът не може да бъде намерен или вече съществува.\n";
    }
}

// Въвеждане на масива с книги от файл(двоичен)

void BinaryInputInvestors(Investor investors[], int& numInvestors, const string& filename) {
    ifstream file(filename, ios::binary);

    if (file.is_open()) {
        file.read((char*)&numInvestors, sizeof(numInvestors));

        for (int i = 0; i < numInvestors; ++i) {
            file.read((char*)&investors[i], sizeof(Investor));
        }

        cout << "Информацията беше прочетена от файла.\n";
        file.close();
    }
    else {
        cout << "Файлът не може да бъде намерен.\n";
    }
}

// Данните в програмата да се четат от файл (текстов).

int loadInvestorsFromFile(const char fileName[], Investor investors[], int& numInvestors)
{
    ifstream file(fileName);

    if (!file)
    {
        cout << endl << "Файлът не може да бъде отворен!";
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

    cout << "Готово";

    return 0;
}


// Данните в програмата да се отпечатват във файл (текстов).

int saveInvestorsToFile(const char fileName[], Investor investors[], int& numInvestors)
{
    ofstream file(fileName, ios::app); /*Данните в програмата да могат да се запазват във файл(текстови) между две стартирания на програмата.*/

    if (!file)
    {
        cout << endl << "Файлът не може да бъде отворен!";
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

    cout << "Готово";

    return 0;
}

// Маин функция с меню

int main() {

    setlocale(LC_ALL, "Bulgarian");

    const string binaryFileName = "binary_file.dat";
    
    Investor investors[50];
    int numInvestors = 0;

    int choice;

    do {
        cout << "\n         Меню\n";
        cout << "1. Добави нов вложител\n";
        cout << "2. Добави списък от вложители\n";
        cout << "3. Изведи всички вложители\n";
        cout << "4. Изведи вложите с BGN влог\n";
        cout << "5. Изведи вложите с максимален влог в EURO\n";
        cout << "6. Справки за влоговете с под меню\n";
        cout << "7. Добавяне на влог за вложители с по-малко от 3 влога\n";
        cout << "8. Изтегляне на сума от влог, по номер на сметка\n";
        cout << "9. Закриване на банков профил\n";
        cout << "10. Подменю за вход/изход с двоични файлове\n";
        cout << "11. Подменю за вход/изход с текстови файлове\n";
        cout << "12. Изход\n";
        cout << "Изберете опция: ";
        cin >> choice;

        if (choice > 12 && choice < 1) {
            cout << "Изберете цяло число от 1 до 12.\n\n";
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
            // подменю
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
                cout << "\nПод Меню\n";
                cout << "1. Въвеждане на масива с книги от файл(двоичен)\n";
                cout << "2. Извеждане на масива с книги във файл(двоичен)\n";
                cout << "3. Връщане към основното меню\n";
                cout << "Изберете опция: ";

                cin >> submenuChoice;

                if (submenuChoice > 3 && submenuChoice < 1) {
                    cout << "Изберете цяло число от 1 до 3.\n\n";
                }

                switch (submenuChoice) {

                case 1:
                    BinaryInputInvestors(investors, numInvestors, binaryFileName);
                    break;
                case 2:
                    BinaryOutputInvestors(investors, numInvestors, binaryFileName);
                    break;
                case 3:
                    cout << "Връщане към основното меню.\n";
                    break;
                }
            } while (submenuChoice != 3);

            break;
        }
        case 11: {
            int submenuChoice;

            do {
                cout << "\nПод Меню\n";
                cout << "1. Въвеждане на масива с книги от файл(текстов)\n";
                cout << "2. Извеждане на масива с книги във файл(текстов)\n";
                cout << "3. Връщане към основното меню\n";
                cout << "Изберете опция: ";

                cin >> submenuChoice;

                if (submenuChoice > 3 && submenuChoice < 1) {
                    cout << "Изберете цяло число от 1 до 3.\n\n";
                }

                switch (submenuChoice) {

                case 1:
                    loadInvestorsFromFile("info.txt", investors, numInvestors);
                    break;
                case 2:
                    saveInvestorsToFile("info.txt", investors, numInvestors);
                    break;
                case 3:
                    cout << "Връщане към основното меню.\n";
                    break;
                }
            } while (submenuChoice != 3);

            break;
        }
        case 12:
            cout << "Излизане от програмата.\n";
            return 0;
        }

    } while (choice != 12);

    return 0;
}
