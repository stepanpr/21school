## ft_server

`docker build . -t ft_server` сборка контейнера

`docker run -it -p 80:80 -p 443:443 ft_server` интерактивный режим

`docker run -td -p 80:80 -p 443:443 ft_server` фоновый режим

`show grants for 'emabel_user'@'localhost;` показать текущие значения привелегий пользователя (в режиме *mysql*)
