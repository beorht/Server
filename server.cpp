#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	/* Переменный для сервера */
	int server_fd, new_socket;
	struct sockadd_in address;
	int addrlen = sizeof( address );
	char buffer[ 1024 ] = { 0 };
	int opt = 1;

	// Создание сервера
	if ( (server_fd = socket( AF_INET, SOCK_STREAM, 0 )) == 0 )
	{
		perror( "Ошибка при создание сокета" );
		exit( EXIT_FAILURE );
	}

	// Настройка опции сокета ( чтобы можно было быстро перезапускать сервер )
	if ( setsockopt( server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt) ) )
	{
		perror( "Ошибка setsockopt" );
		exit( EXIT_FAILURE );
	}

	// Привязка сокета к IP и порту
	address.sin_family 		= AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;    // рандомный IP
	address.sin_port 		= htons( 8000 ); // порт 8000

	if ( bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0 )
	{
		perror( "Ошибка привязки (bind)" );
		exit( EXIT_FAILURE );
	}

	if ( listen(server_fd 3) < 0 )
	{
		perror( "Ошибка listen" );
		exit( EXIT_FAILURE );
	}

	std::cout << "✅ Сервер запущен на порту 8000. Ожидание клиента..." << std::endl;

	if ( (new_socket = accept( server_fd, (struct sockadd *)&address, (socklen_t *)&addrlen )) < 0 )
	{
		perror( "Ошибка accept" );
		exit( EXIT_FAILURE );
	}

	std::cout << "Клиент подключен!" << std::endl;

	// Читаем данные
	int valread = read( new_socket, buffer, 1024 );
	std::cout << "📩 Получено: " << buffer << std::endl;

	// Отправляем обратно
	send( new_socket, buffer, strlen( buffer ), 0 );
	std::cout << "📤 Отправлено обратно клиенту" << std::endl;

	// Закрываем соединение
	close( new_socket );
	close( server_fd );

	return 0;
}
