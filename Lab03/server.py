import socket
import select

# rozmiar "headera" wiadomości
HEADER_LENGTH = 10

# IP i PORT na którym stawiamy serwer
IP = "127.0.0.1"
PORT = 1234

# Stworzenie socketa
# socket.AF_INET - rodzina adresów, IPv4, inne przykłady: AF_INET6, AF_BLUETOOTH, AF_UNIX
# socket.SOCK_STREAM - TCP, połączeniowy; socket.SOCK_DGRAM - UDP, bezpołączeniowy, datagramy; socket.SOCK_RAW - surowe pakiety IP
srv_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Ustawianie opcji socketa
# SO_ - socket option
# SOL_ - socket option level
# Ustawia REUSEADDR na 1 na naszym sockecie (jako opcja poziomu socketa)
# Każe kernelowi używać socketa ponownie jak najszybciej, nie czekając na naturalny czas wygaśnięcia
srv_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# Bind, żeby serwer powiedział systemowi operacyjnemu, że zajmuje dany adres IP i PORT
# Serwer używający adresu 0.0.0.0 słucha na wszystkich dostępnych interfejsach, przydatne do łączenia się lokalnie i z LAN
srv_socket.bind((IP, PORT))

# Przełącza socket w tryb nasłuchiwania
srv_socket.listen()

# Lista socketów dla select.select()
# select() to Unixowy systemcall do monitorowania wielu plików na raz (wielu socketów w naszym przypadku)
sockets_list = [srv_socket]

# Słownik połączonych klientów - socket jako klucz, nagłówek i nazwa użytkownika jako dane
clients = {}

print(f'Listening for connections on {IP}:{PORT}...')

# Handler odbierania wiadomości


def receive_message(client_socket):

    try:

        # Odbieramy nasz "header" zawiera długość wiadomości, jego długość jest zdefiniowana i stała
        message_header = client_socket.recv(HEADER_LENGTH)

        # Jeśli nie otrzymaliśmy nagłówka, to znaczy, że klient zamknął połączenie na przykład przez socket.close()
        # lub socket.shutdown(socket.SHUT_RDWR) - zamknij jedną lub obie połowy połączenia (tu: obie - ReaD, WRite)
        if not len(message_header):
            return False

        # Zamieniamy "header" na inta
        message_length = int(message_header.decode('utf-8').strip())

        # Zwracamy obiekt z nagłówkiem i wiadomością (następne "header" danych z socketa)
        return {'header': message_header, 'data': client_socket.recv(message_length)}

    except:

        # Jeśli tu jesteśmy, to połączenie nie zostało zamknięte poprawnie (np. klient nacisnął ctrl+c)
        # albo zwyczajnie stracił połączenie
        # socket.close() wywołuje również socket.shutdown(socket.SHUT_RDWR) co wysyła informacje o zamknięciu obu połówek połączenia
        # stąd może się pojawić ta pusta wiadomość, której wcześniej szukamy
        return False


while True:

    # Główna pętla programu
    # Wywołuje Unix'owy system call select() albo Windows'owy WinSock call select() z trzema parametrami:
    #   - rlist - lista socketów do monitorowania danych przychodzących
    #   - wlist - sockety, na które możemy coś wysłać (sprawdza, czy bufory nie zawierają danych i socket jest gotowy do wysłania)
    #   - xlist - sockety, na których szukamy wyjątków (chcemy monitorować wszystkie, więc podajemy to samo co do rlist)
    # Zwracane listy:
    #   - reading - sockety, na które otrzymaliśmy dane (żebyśmy nie musieli każdego z osobna pytać w pętli)
    #   - writing - sockety gotowe na nadanie danych (tutaj zmienna zastępcza '_', bo nas to nie obchodzi)
    #   - errors  - sockety z błędami
    # To jest wywołanie blokujące, kod "poczeka" tutaj, aż to zadanie się skończy
    read_sockets, _, exception_sockets = select.select(
        sockets_list, [], sockets_list)

    # Iterujemy przez sockety, które otrzymały dane
    for notified_socket in read_sockets:

        # Jeśli wybrany socket to nasz główny socket - otrzymaliśmy nowe połączenie, zaakceptujmy je
        if notified_socket == srv_socket:

            # Akceptowanie nowego połączenia
            # To daje nam nowy socket - client socket, do niego podłączony jest TYLKO DANY klient, przez niego z nim się komunikujemy
            # Drugi otrzymany obiekt to zestaw IP/PORT
            client_socket, client_address = srv_socket.accept()

            # Klient powinien natychmiast nadać swój username, otrzymajmy go i zapiszmy
            user = receive_message(client_socket)

            # Jeśli go nie otrzymaliśmy to znaczy, że klient się rozłączył zanim nadał swój username
            if user is False:
                continue

            # Dodajemy nowy socket do listy select.select()
            sockets_list.append(client_socket)

            # Zapisujemy username i "header"
            clients[client_socket] = user

            # Wyświetlamy informacje o nowym połączeniu w konsoli
            print('Accepted new connection from {}:{}, username: {}'.format(
                *client_address, user['data'].decode('utf-8')))

        # Jeśli istniejący socket kliencki wysłał wiadomość
        else:

            # Pobieramy otrzymaną wiadomość
            message = receive_message(notified_socket)

            # Jeśli nie otrzymaliśmy wiadomości, klient się rozłączył, posprzątajmy
            if message is False:
                # Wyświetlamy informacje o utraconym połączeniu w konsoli
                print('Closed connection from: {}'.format(
                    clients[notified_socket]['data'].decode('utf-8')))

                # Usuwamy socket z listy socket.socket()
                sockets_list.remove(notified_socket)

                # Usuwamy klienta z naszej listy
                del clients[notified_socket]

                continue

            # Wybieramy użytkownika, któremu odpowiada socket, żebyśmy wiedzieli kto nadał wiadomość
            user = clients[notified_socket]

            # Wyświetlamy informacje o otrzymaniu nowej wiadomości
            print(
                f'Received message from {user["data"].decode("utf-8")}: {message["data"].decode("utf-8")}')

            # Iterujemy po wszystkich połączeniach klienckich i nadajemy na nie otrzymaną wiadomość
            for client_socket in clients:

                # Ale nie wysyłamy jej do nadawcy
                if client_socket != notified_socket:

                    # Wysyłamy username i wiadomość (oba z ich odpowiednimi headerami)
                    # Używamy ponownie headera wiadomości od nawdawcy i zapisany header username'a (z momentu podłączenia klienta)
                    client_socket.send(
                        user['header'] + user['data'] + message['header'] + message['data'])

    # Nie jest to potrzebne, ale jakby coś poszło nie tak to rozwiążmy wyjątki
    for notified_socket in exception_sockets:

        # Usuwamy powiadomiony socket z listy socket.socket()
        sockets_list.remove(notified_socket)

        # Usuwamy odpowiadającego mu klienta
        del clients[notified_socket]
