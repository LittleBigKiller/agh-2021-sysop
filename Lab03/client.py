import socket
import select
import errno
import sys

# rozmiar "headera" wiadomości
HEADER_LENGTH = 10

# IP i PORT serwera
IP = "127.0.0.1"
PORT = 1234

# pobieramy od użytkownika username
my_username = input("Username: ")

# Stworzenie socketa
# socket.AF_INET - rodzina adresów, IPv4, inne przykłady: AF_INET6, AF_BLUETOOTH, AF_UNIX
# socket.SOCK_STREAM - TCP, połączeniowy; socket.SOCK_DGRAM - UDP, bezpołączeniowy, datagramy; socket.SOCK_RAW - surowe pakiety IP
cli_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Łączymy się z podanym IP i PORTem
cli_socket.connect((IP, PORT))

# Ustawiamy połączenie w tryb nieblokujący, więc call .recv() nie będzie czekał na powodzenie,
# jak coś się przedłuży to wyrzuci wyjątek, który rozwiążemy
cli_socket.setblocking(False)

# Przygotowujemy username i jego header
# Musimy zakodować username na bajty, potem policzyć te bajty i przygotować header wiadomości (o stałym rozmiarze), który też zakodujemy
username = my_username.encode('utf-8')
username_header = f"{len(username):<{HEADER_LENGTH}}".encode('utf-8')
# nadajemy header i username w postaci zakodowanej wiadomości
cli_socket.send(username_header + username)

while True:
    # lista możliwych źródeł danych - terminal i socket
    sockets_list = [sys.stdin, cli_socket]

    # analogiczne jak na serwerze wykorzystanie select(), tylko tym razem nie sprawdzamy wyjątków
    read_sockets, write_socket, error_socket = select.select(
        sockets_list, [], [])

    # iterujemy po źródłach danych
    for socks in read_sockets:
        # jeżeli otrzymaliśmy dane na socket (ktoś inny nadał wiadomość i serwer ją podał dalej)
        if socks == cli_socket:
            # odbieramy header username (ten określonej długości)
            username_header = cli_socket.recv(HEADER_LENGTH)

            # jeżeli go nie otrzymaliśmy, to znaczy, że serwer zakończył działanie
            if not len(username_header):
                # wypisujemy informacje o tym na konsolę (można zwykłym printem, ja się bawię :P)
                # kolorujemy output na jasno czerwono [ANSI ESCAPE CODE]
                sys.stdout.write('\u001b[31;1m')
                sys.stdout.write('Connection closed by the server')
                # resetuje kolor outputu na domyślny [ANSI ESCAPE CODE]
                sys.stdout.write('\u001b[0m\n')
                # wymuszam wypisanie danych na terminal
                sys.stdout.flush()

                # kończymy program
                sys.exit()

            # pobieramy z nagłówka długość username, który otrzymaliśmy
            username_length = int(username_header.decode('utf-8').strip())
            # pobieramy username nadawcy
            username = cli_socket.recv(username_length).decode('utf-8')

            # odbieramy header wiadomości (ten określonej długości)
            message_header = cli_socket.recv(HEADER_LENGTH)
            # pobieramy z nagłówka długość wiadomości, którą otrzymaliśmy
            message_length = int(message_header.decode('utf-8').strip())
            # pobieramy treść wiadomości
            message = cli_socket.recv(message_length).decode('utf-8')

            # Wypisujemy wiadomość na chacie
            # kolorujemy output na jasno zielono [ANSI ESCAPE CODE]
            sys.stdout.write('\u001b[32;1m')
            # wypisujemy username
            sys.stdout.write(f'\r{username} ')
            # kolorujemy output na jasno żółto [ANSI ESCAPE CODE]
            sys.stdout.write('\u001b[33;1m')
            # wypisujemy separator obszaru username od treści
            sys.stdout.write(f'> ')
            # resetujemy kolor outputu na domyślny [ANSI ESCAPE CODE]
            sys.stdout.write('\u001b[0m')
            # wypisujemy wiadomość
            sys.stdout.write(f'{message}\n')
            # wymuszam wypisanie danych na terminal (na wszelki wypadek)
            sys.stdout.flush()

        # Jeżeli nie otrzymaliśmy wiadomości z zewnątrz, to musieliśmy ją napisać na terminalu
        else:
            # zczytujemy wiadomość z terminala i usuwamy znak zakończenia linii z jej końca
            message = sys.stdin.readline().rstrip()

            # kodujemy wiadomość na bajty
            message = message.encode('utf-8')
            # tworzymy i kodujemy na bajty nagłówek z informacją o długości naszej wiadomości
            message_header = f"{len(message):<{HEADER_LENGTH}}".encode('utf-8')
            # nadajemy do serwera naszą wiadomość z jej nagłówkiem
            cli_socket.send(message_header + message)

            # Ładne wypisywanie wiadomości (można je zignorować :P)
            # przesuwamy kursor na początek poprzedniej linii, żeby nadpisać wiadomość
            # przez nas wpisaną w terminal [ANSI ESCAPE CODE]
            sys.stdout.write('\033[F')
            # kolorujemy output na jasno zielono [ANSI ESCAPE CODE]
            sys.stdout.write('\u001b[32;1m')
            sys.stdout.write(f'{my_username} ')
            # kolorujemy output na jasno niebiesko [ANSI ESCAPE CODE]
            sys.stdout.write('\u001b[34;1m')
            # wypisujemy oznaczenie
            sys.stdout.write(f'(YOU) ')
            # kolorujemy output na jasno żółto [ANSI ESCAPE CODE]
            sys.stdout.write('\u001b[33;1m')
            # wypisujemy separator obszaru username od treści
            sys.stdout.write(f'> ')
            # resetujemy kolor outputu na domyślny [ANSI ESCAPE CODE]
            sys.stdout.write('\u001b[0m')
            # wypisujemy wiadomość (musimy ją spowrotem zdekodować... to można poprawić :V)
            sys.stdout.write(message.decode('utf-8') + '\n')
            # wymuszam wypisanie danych na terminal (na wszelki wypadek)
            sys.stdout.flush()
