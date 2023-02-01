// std::string find_card(std::map<std::string, long long>& mp, std::vector<long long>& u, long long z) {
//     long long idx = 0;
//     for(std::size_t i = 0; i < u.size(); i++) {
//         if(u[i] == z) {
//             break;
//         } else {
//             idx++;
//         }
//     }
 
//     for (auto& item : mp) {
//         if (idx == 0) {
//             return item.first;
//         }
//         idx--;
//     }
//     return "";
// }