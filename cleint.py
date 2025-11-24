import socket
import threading
import shifr

def connect_server():
	client = socket.socket()
	client.connect( ("localhost", 5050) )

	while True:

		message_potok = threading.Thread( target=get_message, args=(client,) )
		message_potok.start()

	client.close()


def get_message(client):

	while True:

		send_message = input( ">>>" )
		data = shifr.shifr( send_message ) 
		client.send( data.encode( "utf-8" ) )
		
		data_message = client.recv( 10240 )

		if not data:
			break 

		data = data_message.decode( "utf-8" )

		print( data )
		print( shifr.deshifr( data ) )	
		
if __name__ == '__main__':
	connect_server()