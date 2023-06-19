# Rotas de User

- # `POST /user`

	`Registra um novo usuário`

		POST http://localhost:80/user

	```javascript
	{
		"email" : String,
		"username" : String,
		"password" : String
	}
	```
	> 'username', 'email' e 'password' são obrigatórios.
	- ## Resposta
		- Sucesso

			```javascript
			HTTP/1.1 201 Created
			```
			```javascript
			{
				"email": String,
				"username": String
			}
			```
		- Falha
			```javascript
			HTTP/1.1 400 Bad Request
			```
			`Usuário ja registrado`
			```javascript
			{
				"error": "Username or Email already registered."
			}
			```
			`Algum dado requerido faltou`
			```javascript
			{
				"error": "'DADO' is required."
			}
			```
			
			`username invalido`
			```javascript
			{
				"error": "'username' is invalid."
			}
			```
			`email invalido`
			```javascript
			{
				"error": "'email' is invalid."
			}
			```
- # `GET /user:id`

	`Obtém informações do usuário autenticado`

		GET http://localhost:80/user/:id
		Authorization: Bearer <TOKEN>

	- ### Resposta
    	- Sucesso

			```javascript
			HTTP/1.1 200 OK
			```
			```javascript
			{
				"username": String,
				"email": String
			}
			```
			> Para obter o id o usuário deve fazer um post para /auth, a fim de se autenticar.
- # `PUT /user:id`

	`Obtém informações do usuário autenticado`

		PUT http://localhost:80/user/:id
		Authorization: Bearer <TOKEN>

	```javascript
	{
		"email" : String,
		"username" : String,
		"password" : String
	}
	```
    - ### Resposta
      - Sucesso

		```javascript
		HTTP/1.1 200 OK
		```
		```javascript
		{
			"username": String,
			"email": String
		}
		```
- # `Delete /user:id`

	`Remove um usuário`

		DELETE http://localhost:80/user/:id
		Authorization: Bearer <TOKEN>

    - ### Resposta
      - Sucesso

		```javascript
		HTTP/1.1 200 OK
		```
		```javascript
		{
			"ok": "User deleted!"
		}
		```