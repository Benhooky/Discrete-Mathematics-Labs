#include "functions.h"
#include "iostream"
#include <string>
int getnum() {
	bool flag = true;
	std::string user_input;
	int answer;
	while (flag != false) {
		try {
			size_t pos = 0;
			std::cin >> user_input;
			answer = stoi(user_input, &pos);//при невозможности преобразовать string в int будет исключение
			if (pos!=user_input.size()) //нельзя вводить не целые числа
				throw std::invalid_argument("double val");
			flag = false;
		}
		catch (std::exception) {
			std::cout << "Неправильный ввод. Попробуйте ещё раз..\n>";
		}
	}
	return answer;
}


