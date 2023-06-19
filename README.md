# 42Rolls

Projeto realizado para fins de classificação no 42Labs e ajudar jogadores em suas partidas de rpg de mesa.

## Peparando a API

## Com docker

```bash
docker pull 42roll/42roll:api
docker run -t -d --name server 42roll/42roll:api
```

## Sem docker

## Dependencias externas

```bash
apt-get update
apt-get install cmake libssl-dev libsasl2-dev clang make git valgrind python libmongoc-1.0-0 libbson-1.0-0 -y
```

Preparando libmongoc e libbson

```bash
git clone https://github.com/mongodb/mongo-c-driver.git
cd mongo-c-driver
git checkout 1.21.0
python build/calc_release_version.py > VERSION_CURRENT
mkdir cmake-build
cd cmake-build
cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
cmake --build .
cmake --build . --target install
cd ..
cd ..
rm -rf mongo-c-driver
```

Referencia

- [libbson](http://mongoc.org/libmongoc/1.21.0/installing.html)

- [libmongoc](http://mongoc.org/libmongoc/1.21.0/installing.html)

## Executando a API

```bash
cd /root/labs/API
make run
```

## Executando a CLI 

```bash
cd /root/labs/CLI
make && ./cli
```
## Comandos da CLI

 | Comando | Resultando                    |
 | ------- | ----------------------------- |
 | -l      | Mostra uma lista simples      |
 | -c      | Colore de acordo com o método |
 | -a      | Ordena de forma crescente     |
 | -d      | Ordena de forma decrescente   |
 | -G      | Mostra apenas GET             |
 | -P      | Mostra apenas POST            |
 | -U      | Mostra apenas PUT             |
 | -D      | Mostra apenas DELETE          |
 | -O      | Mostra apenas Outras          |
> As flags -G -P -U -D -O, podem ser combinadas.

## Ferramentas

 | Nome     | Função                                                    |
 | -------- | --------------------------------------------------------- |
 | Mongoose | Gerador da interface HTTP                                 |
 | MongoDB  | Gerencia os dados da aplicação                            |
 | Draw.io  | Diagramação e organização do projeto                      |
 | Docker   | Separa, organiza e manter os ambientes isolados e seguros |

 ## Docker

![Docker](/Documentation/static/docker.jpg)

## Arquitetura

![Arquitetura](/Documentation/static/arquitetura.svg)

## Banco de dados

![Database](/Documentation/static/diagrama_relacional.svg)

# API reference

## Header padrão

```http
Content-Type: application/json
Connection: close
Access-Control-Allow-Origin: *
Accept-Language: en, pt-br;q=0.9,*;q=0.8
Allow: GET, POST, PUT, DELETE
```
## Respostas padrão

```javascript
HTTP/1.1 400 Bad Request
```
`:id invalido`
```javascript
{
	"error": "Invalid id."
}
```
`Token invalido`
```javascript
{
	"error": "Invalid token."
}
```
`Token mal formado`
```javascript
{
	"error": "Token mal formated."
}
```
`Token não encontrado`
```javascript
{
	"error": "Token not found."
}
```
`Body invalido`
```javascript
{
	"error": "Invalid body."
}
```
`Usuário não autorizado`
```javascript
HTTP/1.1 401 Unauthorized
```
```javascript
{
	"error": "Not authorized!"
}
```

- ## Root
  
		/

	- GET

		`Obtém informações da API`

		```http
		GET http://localhost:80/
		```
- ## Classe

		/class | /class:id

	- GET

		`Obtém a lista de todas as classes disponíveis.`

		```http
		GET http://localhost:80/class
		```
		Mais informações: [Classe documentação](/Documentation/ref_api/class.md)
	- GET

		`Obtém as informações de uma classe.`

		```http
		GET http://localhost:80/class/:id
		```
		Mais informações: [Classe documentação](/Documentation/ref_api/class.md)
- ## Race

		/race | /race:id

	- GET

		`Obtém a lista de todas as raças disponíveis.`

		```http
		GET http://localhost:80/race
		```
		Mais informações: [Race documentação](/Documentation/ref_api/race.md)
	- GET

		`Obtém as informações de uma raça.`

		```http
		GET http://localhost:80/race/:id
		```
		Mais informações: [Race documentação](/Documentation/ref_api/race.md)
- ## User
		
		/user | /user/:id

	- POST

		`Regista um usuário.`

		```http
		POST http://localhost:80/user
		```
		```javascript
		{
			"username" : String,
			"email" : Boolean,
			"password" : String
		}
		```
		Mais informações: [User documentação](/Documentation/ref_api/user.md)
	- GET

		`Obtém informações do usuário.`

		```http
		GET http://localhost:80/user/:id
		Authorization: Bearer <TOKEN>
		```
		Mais informações: [User documentação](/Documentation/ref_api/user.md)
	- PUT

		`Atualiza algumas informações do usuário.`

		```http
		PUT http://localhost:80/user/:id
		Authorization: Bearer <TOKEN>
		```
		```javascript
		{
			!"username" : String,
			!"email" : Boolean,
			!"password" : String
		}
		```
		Mais informações: [User documentação](/Documentation/ref_api/user.md)
	- DELETE

		`Apaga o registro do usuário.`

		```http
		DELETE http://localhost:80/user/:id
		Authorization: Bearer <TOKEN>
		```
		Mais informações: [User documentação](/Documentation/ref_api/user.md)
- ## Auth

		/auth
	
	- POST

		`Autentica um usuário.` 

		```http
		POST http://localhost:80/auth
		```
		```javascript
		{
			"username" : String,
			"email" : Boolean,
			"password" : String
		}
		```
		Mais informações: [Auth documentação](/Documentation/ref_api/auth.md)
- ## Roll

		/roll | /roll/:id | /roll/:dice

	- POST

		`Realiza uma jogada.`

		```http
		POST http://localhost:80/roll/:dice
		Authorization: Bearer <TOKEN>
		```
		> Dados disponíveis são: D4 D6 D8 D10 D20 D100

		> Ao fazer uma requisição mande apenas os números
		Mais informações: [Roll documentação](/Documentation/ref_api/roll.md)
	- GET

		`Obtém a lista de todas as jogadas feitas.`

		```http
		GET http://localhost:80/roll
		Authorization: Bearer <TOKEN>
		```
		Mais informações: [Roll documentação](/Documentation/ref_api/roll.md)
	- GET

		`Obtém as informações de uma jogada.`

		```http
		GET http://localhost:80/roll/:id
		Authorization: Bearer <TOKEN>
		```
		Mais informações: [Roll documentação](/Documentation/ref_api/roll.md)
	- DELETE

		`Apaga o registro de uma jogada.`

		```http
		DELETE http://localhost:80/roll/:id
		Authorization: Bearer <TOKEN>
		```
		Mais informações: [Roll documentação](/Documentation/ref_api/roll.md)

