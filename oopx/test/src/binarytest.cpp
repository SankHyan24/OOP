// #include <utility.hpp>
// #include <test.hpp>
// #include <myserial.hpp>
// #include <climits>
// #include <random>
// #include <map>
// #include <list>
// #include <vector>
// #include <set>
// #include <tuple>

// using namespace std;
// using namespace BinSerial;
// void binary_test()
// {

//     string file_name = "./testfile.tmp";
//     // 基础测试——int/double/string/vector/set/list/map
//     {
//         int int_b, int_a = Utility::RandUtil::RandomInt(INT_LOW_BOUND, INT_UP_BOUND);
//         serialize(int_a, file_name);
//         deserialize(int_b, file_name);
//         ASSERT_EQ(int_a, int_b);

//         double double_b, double_a = Utility::RandUtil::RandomDouble(0, 100);
//         serialize(double_a, file_name);
//         deserialize(double_b, file_name);
//         ASSERT_EQ(double_a, double_b);

//         string str1, str2;
//         Utility::RandUtil::RandomString(str1, TEST_STR_LEN);
//         serialize(str1, file_name);
//         deserialize(str2, file_name);
//         ASSERT_EQ(str1, str2);

//         vector<int> vec1, vec2;
//         for (int i = 0; i < TEST_ARR_LEN; i++)
//             vec1.push_back(Utility::RandUtil::RandomInt(INT_LOW_BOUND, INT_UP_BOUND));
//         serialize(vec1, file_name);
//         deserialize(vec2, file_name);
//         for (int i = 0; i < TEST_ARR_LEN; i++)
//             ASSERT_EQ(vec1[i], vec2[i]);

//         set<int> set_a, set_b;
//         for (int i = 0; i < TEST_ARR_LEN; i++)
//             set_a.insert(Utility::RandUtil::RandomInt(INT_LOW_BOUND, INT_UP_BOUND));
//         serialize(set_a, file_name);
//         deserialize(set_b, file_name);
//         ASSERT_EQ(set_a.size(), set_b.size());
//         for (auto &i : set_a)
//             ASSERT_NE(set_b.find(i), set_b.end());

//         list<int> list_a, list_b;
//         for (int i = 0; i < TEST_ARR_LEN; i++)
//             list_a.push_back(Utility::RandUtil::RandomInt(INT_LOW_BOUND, INT_UP_BOUND));
//         serialize(list_a, file_name);
//         deserialize(list_b, file_name);
//         ASSERT_EQ(list_a.size(), list_b.size());
//         auto it_list_a = list_a.begin();
//         auto it_list_b = list_b.begin();
//         for (; it_list_a != list_a.end(); it_list_a++, it_list_b++)
//             ASSERT_EQ(*it_list_a, *it_list_b);

//         map<int, int> map_a, map_b;
//         for (int i = 0; i < TEST_ARR_LEN; i++)
//             map_a.insert(make_pair(Utility::RandUtil::RandomInt(INT_LOW_BOUND, INT_UP_BOUND), Utility::RandUtil::RandomInt(INT_LOW_BOUND, INT_UP_BOUND)));
//         serialize(map_a, file_name);
//         deserialize(map_b, file_name);
//         ASSERT_EQ(map_a.size(), map_b.size());
//         auto it_map_a = map_a.begin();
//         auto it_map_b = map_b.begin();
//         for (; it_map_a != map_a.end(); it_map_a++, it_map_b++)
//             ASSERT_EQ(it_map_a->first, it_map_b->first);
//         for (; it_map_a != map_a.end(); it_map_a++, it_map_b++)
//             ASSERT_EQ(it_map_a->second, it_map_b->second);
//     }

//     // 高级测试——容器之间随意多重嵌套
//     {
//         vector<set<int>> vec_set1, vec_set2;
//         for (size_t i = 0; i < TEST_ARR_LEN; i++)
//         {
//             set<int> tmp;
//             int size = Utility::RandUtil::RandomInt(1, TEST_ARR_LEN);
//             for (size_t j = 0; j < size; j++)
//                 tmp.insert(Utility::RandUtil::RandomInt(INT_LOW_BOUND, INT_UP_BOUND));
//             vec_set1.push_back(tmp);
//         }
//         serialize(vec_set1, file_name);
//         deserialize(vec_set2, file_name);
//         for (size_t i = 0; i < TEST_ARR_LEN; i++)
//         {
//             ASSERT_EQ(vec_set1[i].size(), vec_set2[i].size());
//             for (auto &j : vec_set1[i])
//                 ASSERT_EQ(vec_set1[i].count(j), vec_set2[i].count(j));
//         }

//         vector<list<int>> vec_list1, vec_list2;
//         for (size_t i = 0; i < TEST_ARR_LEN; i++)
//         {
//             list<int> tmp;
//             int size = Utility::RandUtil::RandomInt(1, TEST_ARR_LEN);
//             for (size_t j = 0; j < size; j++)
//                 tmp.push_back(Utility::RandUtil::RandomInt(INT_LOW_BOUND, INT_UP_BOUND));
//             vec_list1.push_back(tmp);
//         }
//         serialize(vec_list1, file_name);
//         deserialize(vec_list2, file_name);
//         for (size_t i = 0; i < TEST_ARR_LEN; i++)
//         {
//             ASSERT_EQ(vec_list1[i].size(), vec_list2[i].size());
//             auto it1 = vec_list1[i].begin();
//             auto it2 = vec_list2[i].begin();
//             for (; it1 != vec_list1[i].end(); it1++, it2++)
//                 ASSERT_EQ(*it1, *it2);
//         }

//         vector<vector<int>> vec_vec1, vec_vec2;
//         for (size_t i = 0; i < TEST_ARR_LEN; i++)
//         {
//             int randnum = Utility::RandUtil::RandomInt(INT_LOW_BOUND, TEST_ARR_LEN);
//             vector<int> set1;
//             for (size_t j = 0; j < randnum; j++)
//                 set1.push_back(Utility::RandUtil::RandomInt(INT_LOW_BOUND, INT_UP_BOUND));
//             vec_vec1.push_back(set1);
//         }
//         serialize(vec_vec1, file_name);
//         deserialize(vec_vec2, file_name);
//         ASSERT_EQ(vec_vec1.size(), vec_vec2.size());
//         for (size_t i = 0; i < TEST_ARR_LEN; i++)
//         {
//             ASSERT_EQ(vec_vec1[i].size(), vec_vec2[i].size());
//             for (size_t j = 0; j < vec_vec1[i].size(); j++)
//                 ASSERT_EQ(vec_vec1[i][j], vec_vec2[i][j]);
//         }
//     }

//     remove(file_name.c_str());
//     cout << "Test Done" << endl;
// }