//#include <iostream>
//#include "glMath/glMath.h"
//#include "glm/glm.hpp"
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//int main()
//{
//	glMath::vec3f a(-3, 5, 6);
//	glMath::mat4f m = glMath::mat4f(1.0);
//	glm::mat4 model = glm::mat4(1.0f);
//
//	m = glMath::translate(m, a);
//	model = glm::translate(model, glm::vec3(-3, 5, 6));
//
//	m= glMath::rotate(m, glMath::radians(-90.f), glMath::vec3f(0, 0, 1));
//	model= glm::rotate(model, glm::radians(-90.f), glm::vec3(0, 0, 1));
//
//	m = glMath::scale(m, glMath::vec3f(1, 2, 3));
//	model = glm::scale(model, glm::vec3(1, 2, 3));
//	//
//	//glMath::mat4f m = glMath::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
//	//std::cout << "Orthographic:\n" << m << std::endl;
//
//	//m = glMath::perspective(glMath::radians(45.0f), 800.f / 600, 0.1f, 100.0f);
//	//model = glm::perspective(glm::radians(45.0f), 800.f / 600, 0.1f, 100.0f);
//
//	//m = glMath::lookAt(glMath::vec3f(0,0,3), glMath::vec3f(0,0,2), glMath::vec3f(0,1,0));
//	//model = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,2), glm::vec3(0,1,0));
//
//	std::cout << "glMath:\n" << m<< std::endl;
//	std::cout << "glm:\n" << std::endl;
//	
//	std::cout<< model[0].x << " " << model[1].x << " " << model[2].x<< " " << model[3].x  << std::endl;
//	std::cout<< model[0].y << " " << model[1].y << " " << model[2].y << " " << model[3].y << std::endl;
//	std::cout<< model[0].z << " " << model[1].z << " " << model[2].z << " " << model[3].z << std::endl;
//	std::cout<< model[0].w << " " << model[1].w << " " << model[2].w << " " << model[3].w << std::endl;
//
//	std::cout<< model[0].x << " " << model[0].y << " " << model[0].z<< " " << model[0].w  << std::endl;
//	std::cout<< model[1].x << " " << model[1].y << " " << model[1].z << " " << model[1].w << std::endl;
//	std::cout<< model[2].x << " " << model[2].y << " " << model[2].z << " " << model[2].w << std::endl;
//	std::cout<< model[3].x << " " << model[3].y << " " << model[3].z << " " << model[3].w << std::endl;
//}