#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

//========================================

struct products {
    string productName,
            subtype,
            price,
            manDate,
            expDate,
            Id,
            type;
};

//--------------------Classes--------------------


class mall {
public:
    void set_username(string un) {username = un;}
    void set_password(string pw) {password = pw;}

    string get_username() { return username;}

    bool Login(vector<string>&);
    void RemoveProduct(vector<products> &, string &, char);


protected:
    string username, password;
};

class persons: public mall {
public:
    string get_firstName() { return firstName;}
    string get_lastName() { return lastName;}
    string get_birthday() { return birthday;}
    string get_gender() { return gender;}
    string get_Id() { return Id;}
    string get_type() { return type;}

    int GetCredit() {return credit;}
    void GetMyPro(vector<products> &) ;
    friend void SignUp(vector<string> &, bool &, int &, char &);

protected:
    string Id, type;
    vector<string> myPro;
    int credit = 0;

private:
    string firstName,
            lastName,
            birthday,
            gender;

};

class customers: public persons {
public:
    void Buy(string &, int&);
    void CancelBuy(string &, int &);
    void IncCredit(string &);
    friend void mall :: RemoveProduct(vector<products> &, string &, char);
    friend int PsProCheck(string, char, int);

};

class admins: public mall {
public:
    void GetPerson(string &);
    void GetPersons(vector<string> &);
    void RemovePerson(string &);
    void AddAdmin(vector<string> &);
    void RemoveExpPro();
};

class sellers: public persons {
public:
    void AddProduct(vector<string> &, int);
    void UpdateProduct(vector<string> &);
    friend void mall :: RemoveProduct(vector<products> &, string &, char);
    friend void customers :: Buy(string &, int &);
    friend int PsProCheck(string, char, int);
    friend void customers :: CancelBuy(string &, int &);
    friend void customers :: Buy(string &, int &);
    friend void admins :: RemovePerson(string &);

private:
    vector<string> SoldPro;
};

//--------------------------------------------------


//-------------Global--Variables-----------------------------

vector<admins> admin(1);
vector<sellers> seller;
vector<customers> customer;
vector<products> unSoldProduct;
vector<products> soldProduct;

//-----------------------------------------------------------

vector<int> ProChecker(vector<products> &, string &, int);
void GetProducts(vector<string> &);
void GetProduct(string &);
vector<string> splitter(string , char);
int PsProCheck(string , char, int);
void functions(vector<string> &, bool &, int &, char &);




int main() {
    string sentence;
    vector<string> strComponents;
    int loginIndex;
    bool checkLogin = false;
    char whoLogin = '+';

    admin[0].set_username("admin");
    admin[0].set_password("admin");

    srand(time(0));

    while (getline(cin,sentence)) {
        if(sentence == "exit")
            return 0;
        strComponents = splitter(sentence , ' ');
        functions(strComponents, checkLogin, loginIndex, whoLogin);
    }
    return 0;
}




//&&&&&&&&&&&&&&&&&---Class_Functions---&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

bool mall :: Login(vector<string>& info) {
    if(info[1] == username) {
        if (info[2] == password){
            return true;
        }
        else
            return false;
    }

    return false;
}

void sellers :: AddProduct(vector<string>& info, int logIndex) {
    products temp;

    temp.Id = info[1];
    temp.productName = info[2];
    temp.type = info[3];
    temp.subtype = info[4];
    temp.price = info[5];
    temp.manDate = info[6];
    temp.expDate = info[7];

    unSoldProduct.push_back(temp);

    seller[logIndex].myPro.push_back(temp.Id);

    cout << "Task done." << endl;
}

void admins :: GetPerson(string& info) {

    for (int i = 0; i < seller.size(); ++i) {
        if (seller[i].get_Id() == info) {
            cout << seller[i].get_Id() << ", ";
            cout << seller[i].get_username() << ", ";
            cout << seller[i].get_firstName() << ", ";
            cout << seller[i].get_lastName() << ", ";
            cout << seller[i].get_birthday() << ", ";
            cout << seller[i].get_gender() << ", ";
            cout << seller[i].get_type() << endl;
            return;
        }
    }
    for (int i = 0; i < customer.size(); ++i) {
        if (customer[i].get_Id() == info) {
            cout << customer[i].get_Id() << ", ";
            cout << customer[i].get_username() << ", ";
            cout << customer[i].get_firstName() << ", ";
            cout << customer[i].get_lastName() << ", ";
            cout << customer[i].get_birthday() << ", ";
            cout << customer[i].get_gender() << ", ";
            cout << customer[i].get_type() << endl;
            return;
        }
    }
    cout << "This Id does not exist." << endl;

}

void admins :: GetPersons(vector<string> & info) {
    if (info.size() == 2) {
        if (info[1] == "customer") {
            for (int i = 0; i < customer.size(); ++i) {
                cout << customer[i].get_Id() << ", ";
                cout << customer[i].get_username() << ", ";
                cout << customer[i].get_type() << endl;
            }
        }
        else if (info[1] == "seller") {
            for (int i = 0; i < seller.size(); ++i) {
                cout << seller[i].get_Id() << ", ";
                cout << seller[i].get_username() << ", ";
                cout << seller[i].get_type() << endl;
            }
        }
    }
    else {
        for (int i = 0; i < customer.size(); ++i) {
            cout << customer[i].get_Id() << ", ";
            cout << customer[i].get_username() << ", ";
            cout << customer[i].get_type() << endl;
        }
        for (int i = 0; i < seller.size(); ++i) {
            cout << seller[i].get_Id() << ", ";
            cout << seller[i].get_username() << ", ";
            cout << seller[i].get_type() << endl;
        }
    }
}

void admins :: RemovePerson(string & info) {
    for (int i = 0; i < customer.size(); ++i) {
        if (customer[i].get_Id() == info) {
            customer.erase(customer.begin() + i);
            cout << "Task done." << endl;
            return;
        }
    }
    for (int i = 0; i < seller.size(); ++i) {
        if (seller[i].get_Id() == info) {
            while (seller[i].myPro.size() > 0)
                RemoveProduct(unSoldProduct, seller[i].myPro[0], 'S');
            seller.erase(seller.begin() + i);

            cout << "Task done." << endl;
            return;
        }
    }
    cout << "This Id does not exist." << endl;
}

void admins :: AddAdmin(vector<string> & info) {
    admin.resize(admin.size() + 1);
    admin[admin.size() - 1].set_username(info[1]);
    admin[admin.size() - 1].set_password(info[2]);
    cout << "Task done." << endl;
}

void mall :: RemoveProduct(vector <products> & pList, string & info, char c) {
    int n = ProChecker(pList, info, 6)[0];

    if (n >= 0) {
        pList.erase(pList.begin() + n);

        if (c == 'S') {
            for (int i = 0; i < seller.size(); ++i) {
                for (int j = 0; j < seller[i].myPro.size(); ++j) {
                    if (seller[i].myPro[j] == info) {
                        seller[i].myPro.erase(seller[i].myPro.begin() + j);
                        return;
                    }
                }
            }
        }
        if (c = 'C') {
            for (int i = 0; i < customer.size(); ++i) {
                for (int j = 0; j < customer[i].myPro.size(); ++j) {
                    if (customer[i].myPro[j] == info) {
                        customer[i].myPro.erase(customer[i].myPro.begin() + j);
                        return;
                    }
                }
            }
        }
    }
    cout << "This product Id does not exist." << endl;
}

void sellers :: UpdateProduct(vector<string> & info) {
    int tmpNum;
    if (info.size() > 2) {
        tmpNum = ProChecker(unSoldProduct, info[1], 6)[0];

        for (int i = 2; i < info.size(); i += 2) {
            if (info[i] == "-n")
                unSoldProduct[tmpNum].productName = info[i + 1];
            if (info[i] == "-p")
                unSoldProduct[tmpNum].price = info[i + 1];
            if (info[i] == "-t")
                unSoldProduct[tmpNum].type = info[i + 1];
            if (info[i] == "-st")
                unSoldProduct[tmpNum].subtype = info[i + 1];
        }
    }
}

void customers :: Buy(string & info, int & lIndex) {
    int n = ProChecker(unSoldProduct, info, 6)[0];
    int inx = PsProCheck(info, 'S', 0);

    if (n >= 0) {
        if (customer[lIndex].GetCredit() >= stoi(unSoldProduct[n].price)) {
            customer[lIndex].credit -= stoi(unSoldProduct[n].price);
            seller[inx].credit += stoi(unSoldProduct[n].price);
            soldProduct.push_back(unSoldProduct[n]);
            seller[inx].SoldPro.push_back(info);
            seller[inx].RemoveProduct(unSoldProduct, info, 'S');
            customer[lIndex].myPro.push_back(info);

            cout << "Task done." << endl;
        }

        else cout << "You don't have enough money." << endl;
    }
    else cout << "This product Id does not exist." << endl;


}

void persons :: GetMyPro(vector<products> & pList) {
    int n;
    if (myPro.size() > 0) {
        for (int i = 0; i < myPro.size(); ++i) {
            n = ProChecker(pList, myPro[i], 6)[0];
            if (n >= 0) {
                cout << pList[n].Id << ", ";
                cout << pList[n].productName << ", ";
                cout << pList[n].price << ", ";
                cout << pList[n].manDate << ", ";
                cout << pList[n].expDate << ", ";
                cout << pList[n].type << ", ";
                cout << pList[n].subtype << endl;
            }
        }
    }
    else cout << "Nothing!" << endl;
}

void customers :: IncCredit(string & value) {credit += stoi(value);}

void admins :: RemoveExpPro() {
    vector<string> temp;
    vector<string> expTime;
    const int MAXLEN = 80;
    char d[MAXLEN], m[MAXLEN], y[MAXLEN];
    time_t t = time(0);
    strftime(y, MAXLEN, "%Y", localtime(&t));
    strftime(m, MAXLEN, "%m", localtime(&t));
    strftime(d, MAXLEN, "%d", localtime(&t));
    int year = stoi(y);
    int month = stoi(m);
    int day = stoi(d);

    for (int i = 0; i < unSoldProduct.size(); ++i) {
        expTime = splitter(unSoldProduct[i].expDate, '/');
        if (stoi(expTime[2]) == year) {
            if (stoi(expTime[0]) == month) {
                if (stoi(expTime[1]) == day) {
                    continue;
                }
                else if (stoi(expTime[1]) < day){
                    temp.push_back(unSoldProduct[i].Id);
                }
            }
            else if (stoi(expTime[2]) < month) {
                temp.push_back(unSoldProduct[i].Id);
            }
        }
        else if (stoi(expTime[2]) < year) {
            temp.push_back(unSoldProduct[i].Id);
        }
    }
    cout << temp.size() <<endl;
    for (int i = 0; i < temp.size(); ++i) {
        RemoveProduct(unSoldProduct, temp[i], 'S');
    }
    cout << "Task done." << endl;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


//************************--Functions---***************************************************

void SignUp(vector<string> & info, bool & isLogin, int & lIndex, char & whoLogin) {
    if (!isLogin) {
        if (info[1] == "customer") {
            customer.resize(customer.size() + 1);
            lIndex = customer.size() - 1;
            whoLogin = 'C';
            customer[lIndex].type = info[1];
            customer[lIndex].username = info[2];
            customer[lIndex].password = info[3];
            customer[lIndex].firstName = info[4];
            customer[lIndex].lastName = info[5];
            customer[lIndex].birthday = info[6];
            customer[lIndex].gender = info[7];
            customer[lIndex].Id = to_string(rand()%(20000) + 10000);
        }
        if (info[1] == "seller") {
            seller.resize(seller.size() + 1);
            lIndex = seller.size() - 1;
            whoLogin = 'S';
            seller[lIndex].type = info[1];
            seller[lIndex].username = info[2];
            seller[lIndex].password = info[3];
            seller[lIndex].firstName = info[4];
            seller[lIndex].lastName = info[5];
            seller[lIndex].birthday = info[6];
            seller[lIndex].gender = info[7];
            seller[lIndex].Id = to_string(rand()%(20000) + 10000);
        }
        isLogin = true;
        cout << "Task done." << endl;
    }
    else cout << "First quit." << endl;
}

vector<int> ProChecker(vector<products> & pList, string & s, int x) {
    vector<int> temp;
    switch (x) {
        case 0: {
            for (int i = 0; i < pList.size(); ++i) {
                if (pList[i].type == s) {
                    temp.push_back(i);
                }
            }
            break;
        }
        case 1: {
            for (int i = 0; i < pList.size(); ++i) {
                if (pList[i].subtype == s) {
                    temp.push_back(i);
                }
            }
            break;
        }
        case 2: {
            for (int i = 0; i < pList.size(); ++i) {
                if (pList[i].manDate == s) {
                    temp.push_back(i);
                }
            }
            break;
        }
        case 3: {
            for (int i = 0; i < pList.size(); ++i) {
                if (pList[i].expDate == s) {
                    temp.push_back(i);
                }
            }
            break;
        }
        case 4: {
            for (int i = 0; i < pList.size(); ++i) {
                if (stoi(pList[i].price) >= stoi(s)) {
                    temp.push_back(i);
                }
            }
            break;
        }
        case 5: {
            for (int i = 0; i < pList.size(); ++i) {
                if (stoi(pList[i].price) <= stoi(s)) {
                    temp.push_back(i);
                }
            }
            break;
        }
        case 6: {
            for (int i = 0; i < pList.size(); ++i) {
                if (pList[i].Id == s) {
                    temp.push_back(i);
                    break;
                }
            }
            temp.push_back(-1);
            break;
        }
        default: break;
    }
    return temp;
}

void GetProducts(vector<string>& info) {
    if (info.size() > 1) {
        vector<int> ProNumbers, temp;
        int counter = 0, countMax = 0;
        for (int i = 1; i < info.size(); i = i + 2) {
            if (info[i] == "-t") {
                ProNumbers = ProChecker(unSoldProduct, info[i + 1], 0);
                temp.insert(temp.end(), ProNumbers.begin(), ProNumbers.end());
                ProNumbers.clear();
            }
            if (info[i] == "-st") {
                ProNumbers = ProChecker(unSoldProduct, info[i + 1], 1);
                temp.insert(temp.end(), ProNumbers.begin(), ProNumbers.end());
                ProNumbers.clear();
            }
            if (info[i] == "-man") {
                ProNumbers = ProChecker(unSoldProduct, info[i + 1], 2);
                temp.insert(temp.end(), ProNumbers.begin(), ProNumbers.end());
                ProNumbers.clear();
            }
            if (info[i] == "-exp") {
                ProNumbers = ProChecker(unSoldProduct, info[i + 1], 3);
                temp.insert(temp.end(), ProNumbers.begin(), ProNumbers.end());
                ProNumbers.clear();
            }
            if (info[i] == "-minP") {
                ProNumbers = ProChecker(unSoldProduct, info[i + 1], 4);
                temp.insert(temp.end(), ProNumbers.begin(), ProNumbers.end());
                ProNumbers.clear();
            }
            if (info[i] == "-maxP") {
                ProNumbers = ProChecker(unSoldProduct, info[i + 1], 5);
                temp.insert(temp.end(), ProNumbers.begin(), ProNumbers.end());
                ProNumbers.clear();
            }
        }

        sort(temp.begin(), temp.end());
        while (temp.size() != 0) {
            int j = 1;
            counter = 1;
            if (temp.size() > 1) {
                while (temp[0] == temp[j]) {
                    counter++;
                    j++;
                    if (j == temp.size())
                        break;
                }
            }
            if (counter > countMax) {
                ProNumbers.clear();
                ProNumbers.push_back(temp[0]);
                countMax = counter;
            } else if (counter == countMax)
                ProNumbers.push_back(temp[0]);
            temp.erase(temp.begin(), temp.begin() + counter);
        }

        for (int i = 0; i < ProNumbers.size(); ++i) {
            cout << unSoldProduct[ProNumbers[i]].Id << ", ";
            cout << unSoldProduct[ProNumbers[i]].productName << ", ";
            cout << unSoldProduct[ProNumbers[i]].price << ", ";
            cout << unSoldProduct[ProNumbers[i]].type << endl;
        }
    }
    else {
        for (int i = 0; i < unSoldProduct.size(); ++i) {
            cout << unSoldProduct[i].Id << ", ";
            cout << unSoldProduct[i].productName << ", ";
            cout << unSoldProduct[i].price << ", ";
            cout << unSoldProduct[i].type << endl;
        }
    }

}

void GetProduct(string& info) {
    int proNum;
    proNum = ProChecker(unSoldProduct, info, 6)[0];

    cout << unSoldProduct[proNum].Id << ", ";
    cout << unSoldProduct[proNum].productName << ", ";
    cout << unSoldProduct[proNum].price << ", ";
    cout << unSoldProduct[proNum].manDate << ", ";
    cout << unSoldProduct[proNum].expDate << ", ";
    cout << unSoldProduct[proNum].type << ", ";
    cout << unSoldProduct[proNum].subtype << endl;
}

int PsProCheck(string info, char c, int x) {
    if (c == 'S') {
        if (x == 0) {
            for (int i = 0; i < seller.size(); ++i) {
                for (int j = 0; j < seller[i].myPro.size(); ++j) {
                    if (seller[i].myPro[j] == info)
                        return i;
                }
            }
        }
        if (x == 1) {
            for (int i = 0; i < seller.size(); ++i) {
                for (int j = 0; j < seller[i].SoldPro.size(); ++j) {
                    if (seller[i].SoldPro[j] == info)
                        return i;
                }
            }
        }
    }
    if (c == 'C') {
        for (int i = 0; i < customer.size(); ++i) {
            for (int j = 0; j < customer[i].myPro.size(); ++j) {
                if (customer[i].myPro[j] == info)
                    return i;
            }
        }
    }
}

void customers :: CancelBuy(string & info, int & lIndex) {
    int n = ProChecker(soldProduct, info, 6)[0];
    int inx = PsProCheck(info, 'S', 1);

    if (n >= 0) {
        customer[lIndex].credit += stoi(soldProduct[n].price);
        seller[inx].credit -= stoi(soldProduct[n].price);
        unSoldProduct.push_back(soldProduct[n]);
        customer[lIndex].RemoveProduct(soldProduct, info, 'C');
        seller[inx].myPro.push_back(info);

        for (int i = 0; i < seller[inx].SoldPro.size(); ++i) {
            if(seller[inx].SoldPro[i] == info) {
                seller[inx].SoldPro.erase(seller[inx].SoldPro.begin() + i);
                break;
            }
        }

    }

}

vector<string> splitter(string sentence , char delimiter) {
    vector<string> temp;
    int pos = 0;

    while (pos != string::npos) {
        pos = sentence.find(delimiter);

        if (pos == -1) {
            temp.push_back(sentence);
            break;
        }

        temp.push_back(sentence.substr(0,pos));
        sentence = sentence.substr(pos + 1);

    }

    return temp;
}

void functions(vector<string>& info, bool& checkLogin, int& loginIndex, char& whoLogin) {
    if (info[0] == "signup") {
        SignUp(info, checkLogin, loginIndex , whoLogin);

    }
    else if (info[0] == "login") {
        if(!checkLogin) {
            for (int i = 0; i < customer.size(); ++i) {
                if (customer[i].Login(info)) {
                    loginIndex = i;
                    checkLogin = true;
                    whoLogin = 'C';
                    cout << "Task done." << endl;
                    break;
                }
            }

            if (!checkLogin) {
                for (int i = 0; i < seller.size(); ++i) {
                    if (seller[i].Login(info)) {
                        loginIndex = i;
                        checkLogin = true;
                        whoLogin = 'S';
                        cout << "Task done." << endl;
                        break;
                    }
                }
            }

            if (!checkLogin) {
                for (int i = 0; i < admin.size(); ++i) {
                    if (admin[i].Login(info)) {
                        loginIndex = i;
                        checkLogin = true;
                        whoLogin = 'A';
                        cout << "Task done." << endl;
                        break;
                    }
                }
            }
            if (!checkLogin)
                cout << "Username or Password is not correct." << endl;
        }
        else
            cout << "Another account is log in. Please first quit." << endl;
    }
    else if (info[0] == "quit") {
        if (checkLogin) {
            switch (whoLogin) {

                case 'C': {
                    cout << "Task done." << endl;
                    checkLogin = false;
                    whoLogin = '+';
                    break;
                }
                case 'S': {
                    cout << "Task done." << endl;
                    checkLogin = false;
                    whoLogin = '+';
                    break;
                }
                case 'A': {
                    cout << "Task done." << endl;
                    checkLogin = false;
                    whoLogin = '+';
                    break;
                }
                default: {
                    cout << "Login first." << endl;
                }
            }
        }
        else cout << "First login." << endl;
    }
    else if (info[0] == "getProducts") {
        GetProducts(info);
    }
    else if (info[0] == "getProduct") {
        GetProduct(info[1]);
    }
    else if (whoLogin == 'A') {
        if (info[0] == "getPerson") {
            admin[loginIndex].GetPerson(info[1]);
        }
        else if (info[0] == "getPersons") {
            admin[loginIndex].GetPersons(info);
        }
        else if (info[0] == "removePerson") {
            admin[loginIndex].RemovePerson(info[1]);
        }
        else if (info[0] == "addAdmin") {
            admin[loginIndex].AddAdmin(info);
        }
        else if (info[0] == "removeExpiredProducts") {
            admin[loginIndex].RemoveExpPro();
        }
        else if (info[0] == "removeProduct") {
            admin[loginIndex].RemoveProduct(unSoldProduct, info[1], 'S');
        }
        else
            cout << "Bad syntax." << endl;
    }
    else if(whoLogin == 'S') {
        if (info[0] == "addProduct") {
            seller[loginIndex].AddProduct(info, loginIndex);
        }
        else if (info[0] == "removeProduct") {
            seller[loginIndex].RemoveProduct(unSoldProduct, info[1], 'S');
        }
        else if (info[0] == "getMyProducts") {
            seller[loginIndex].GetMyPro(unSoldProduct);
        }
        else if (info[0] == "updateProduct") {
            seller[loginIndex].UpdateProduct(info);
            cout << "Task done." << endl;
        }
        else if (info[0] == "getCredit") {
            cout << seller[loginIndex].GetCredit() << endl;
        }
        else
            cout << "Bad syntax." << endl;
    }
    else if (whoLogin == 'C') {
        if (info[0] == "buy") {
            customer[loginIndex].Buy(info[1], loginIndex);
        }
        else if (info[0] == "getMyProducts") {
            customer[loginIndex].GetMyPro(soldProduct);
        }
        else if (info[0] == "removeProduct") {
            customer[loginIndex].CancelBuy(info[1], loginIndex);
            cout << "Task done." << endl;
        }
        else if (info[0] == "getCredit") {
            cout << customer[loginIndex].GetCredit() << endl;
        }
        else if (info[0] == "IncreaseCredit") {
            customer[loginIndex].IncCredit(info[1]);
        }
        else
            cout << "Bad syntax." << endl;
    }
    else if (info[0] == "getProduct" || info[0] == "removePerson" || info[0] == "addAdmin" ||
            info[0] == "removeExpiredProducts" || info[0] == "removeProduct" || info[0] == "getPersons"
            || info[0] == "addProduct" || info[0] == "getCredit" || info[0] == "updateProduct" ||
            info[0] == "getMyProducts" || info[0] == "buy" || info[0] == "IncreaseCredit") {

        cout << "First login." << endl;
    }
    else
        cout << "Bad syntax." << endl;
}

//**********************************************************************************************