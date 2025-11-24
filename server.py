import socket
import threading
import shifr

def main_server():
	server = socket.socket()
	server.bind( ("", 5050) )

	print( "Server connect!!!" )

	while True:
		server.listen(3)

		connect, address = server.accept()
		print( "Connect: ", connect )

		message_potok = threading.Thread( target=get_message, args=(connect,) )
		message_potok.start()



	server.close()

def get_message( connect ):
	while True:
		get_message = connect.recv(10240)

		if not get_message:
			break 


		data = get_message.decode( "utf-8" )

		print( data )
		print( shifr.deshifr( data ) )		

		send_message = input( ">>>" )
		data = shifr.shifr( send_message ) 
		connect.send( data.encode( "utf-8" ) )

if __name__ == '__main__':
	main_server()