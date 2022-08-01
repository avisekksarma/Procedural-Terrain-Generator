// #pragma once
// #include <unordered_map>
// #include <utility>
// #include <string>
// #include <./glMath.h>
// #include <iostream>

// class ZBuffer
// {
//     struct Plane
//     {
//         float A, B, C, D;
//     };
//     Plane plane;

// public:
//     std::map<std::pair<int, int>, float> depth;

//     void makePlaneEquation(glMath::vec3f p1, glMath::vec3f p2, glMath::vec3f p3)
//     {
//         glMath::vec3f f1 = p2 - p1;
//         glMath::vec3f f2 = p3 - p1;
//         f1 = glMath::cross<float>(f1, f2);
//         float val = f1.dotProduct(p1);
//         // if(p1.x==1 and p1.y==2 and p1.z==-2){
//         //     std::cout<<"------------DEBUG plane eqn------------"<<std::endl;
//         //     std::cout<<f1.x<<" "<<f1.y<<" "<<f1.z<<" "<<-val<<std::endl;
//         //     std::cout<<"------------DEBUG plane eqn end------------"<<std::endl;
//         //     return;
//         // }
//         plane.A = f1.x;
//         plane.B = f1.y;
//         plane.C = f1.z;
//         plane.D = -val;
//     }
//     bool updateDepth(int x, int y, float z)
//     {
//         auto it = depth.find({x, y});
//         if (it != depth.end())
//         {
//             // std::cout << "--------it--------" << std::endl;
//             // std::cout << it->first.first << " " << it->first.second << std::endl;
//             // std::cout << it->second << " " << z << std::endl;
//             // std::cout << "--------it end --------" << std::endl;
//         }
//         if (it == depth.end())
//         {
//             depth.insert({{x, y}, z});
//             return true;
//         }
//         else
//         {
//             if (it->second > z)
//             {
//                 depth.insert({{x, y}, z});
//                 return true;
//             }
//             return false;
//         }
//     }
//     // returns the z value after the x and y are given of plane equation.
//     float returnZ(int x, int y)
//     {
//         float val = -plane.D - plane.A * x - plane.B * y;
//         val = val * (1 / plane.C);
//         return val;
//     }
// };

// class ZBuffer
// {
//     struct Plane
//     {
//         float A, B, C, D;
//     };
//     Plane plane;

// public:
//     std::unordered_map<std::string, float> depth;

//     void makePlaneEquation(glMath::vec3f p1, glMath::vec3f p2, glMath::vec3f p3)
//     {
//         glMath::vec3f f1 = p2 - p1;
//         glMath::vec3f f2 = p3 - p1;
//         f1 = glMath::cross<float>(f1, f2);
//         float val = f1.dotProduct(p1);
//         // if(p1.x==1 and p1.y==2 and p1.z==-2){
//         //     std::cout<<"------------DEBUG plane eqn------------"<<std::endl;
//         //     std::cout<<f1.x<<" "<<f1.y<<" "<<f1.z<<" "<<-val<<std::endl;
//         //     std::cout<<"------------DEBUG plane eqn end------------"<<std::endl;
//         //     return;
//         // }
//         plane.A = f1.x;
//         plane.B = f1.y;
//         plane.C = f1.z;
//         plane.D = -val;
//     }
//     bool updateDepth(int x, int y, float z)
//     {
//         std::string key = std::to_string(x) + ',' + std::to_string(y);
//         auto it = depth[key];
//         if (depth[key] != depth.end())
//         {
//             // std::cout << "--------it--------" << std::endl;
//             // std::cout << it->first.first << " " << it->first.second << std::endl;
//             // std::cout << it->second << " " << z << std::endl;
//             // std::cout << "--------it end --------" << std::endl;
//         }
//         if (it == depth.end())
//         {
//             depth[key] = z;
//             return true;
//         }
//         else
//         {
//             if (depth[key] > z)
//             {
//                 depth[key] = z;
//                 return true;
//             }
//             return false;
//         }
//     }
//     // returns the z value after the x and y are given of plane equation.
//     float returnZ(int x, int y)
//     {
//         float val = -plane.D - plane.A * x - plane.B * y;
//         val = val * (1 / plane.C);
//         return val;
//     }
// };
