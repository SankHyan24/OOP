#include <xmlserial.hpp>
#include <utility.hpp>
#include <test.hpp>

#include <climits>
#include <random>
#include <map>
#include <list>
#include <vector>
#include <set>
using namespace std;
//用户类
class User
{
public:
    User()
    {
        gender = 0;
    };

    User(const string &userName, const string &password, int gender, const string &mobile, const string &email)
    {
        this->userName = userName;
        this->password = password;
        this->gender = gender;
        this->mobile = mobile;
        this->email = email;
    };

    string userName;
    string password;
    int gender;
    string mobile;
    string email;
};

// function:insert XML node
// param:xmlPath:xml文件路径; user:用户对象
// return:0:成功; 非0:失败
int insertXMLNode(const char *xmlPath, const User &user)
{
    XMLDocument doc;
    int res = doc.LoadFile(xmlPath);
    if (res != 0)
    {
        cout << "load xml file failed" << endl;
        return res;
    }
    XMLElement *root = doc.RootElement();

    XMLElement *userNode = doc.NewElement("User");
    userNode->SetAttribute("Name", user.userName.c_str());
    userNode->SetAttribute("Password ", user.password.c_str());
    root->InsertEndChild(userNode);

    XMLElement *gender = doc.NewElement("Gender");
    char buf[100];
    XMLText *genderText = doc.NewText(itoa(user.gender, buf, 10));
    gender->InsertEndChild(genderText);
    userNode->InsertEndChild(gender);

    XMLElement *mobile = doc.NewElement("Mobile");
    mobile->InsertEndChild(doc.NewText(user.mobile.c_str()));
    userNode->InsertEndChild(mobile);

    XMLElement *email = doc.NewElement("Email");
    email->InsertEndChild(doc.NewText(user.email.c_str()));
    userNode->InsertEndChild(email);

    return doc.SaveFile(xmlPath);
}
int createXML(const char *xmlPath)
{
    const char *declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
    XMLDocument doc;
    doc.Parse(declaration); //会覆盖xml所有内容

    //添加申明可以使用如下两行
    // XMLDeclaration* declaration=doc.NewDeclaration();
    // doc.InsertFirstChild(declaration);

    XMLElement *root = doc.NewElement("serialization");
    doc.InsertEndChild(root);

    return doc.SaveFile(xmlPath);
}
void xml_test()
{
    User user("zhangsan", "123456", 1, "13800138000", "3200105788@zju.edu.cn");
    const char *xmlPath = "./test.xml";
    int res = createXML(xmlPath);
    if (res != 0)
    {
        cout << "create xml file failed" << endl;
        return;
    }
    res = insertXMLNode(xmlPath, user);
    if (res != 0)
    {
        cout << "insert xml node failed" << endl;
        return;
    }
}