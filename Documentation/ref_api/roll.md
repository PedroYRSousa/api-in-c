# Rotas de Roll

- # `POST /roll/:dice`

	`Realiza uma jogada.`

		POST http://localhost:80/roll/:dice
		Authorization: Bearer <TOKEN>

	> Dados disponíveis são: D4 D6 D8 D10 D20 D100

	> Ao fazer uma requisição mande apenas os números
	- ## Resposta
		- Sucesso

			```javascript
			HTTP/1.1 201 Created
			```
			```javascript
			{
				"date": {
					"$date": {
						"$numberLong": "1645944914954"
					}
				},
				"result": {
					"$numberInt": "54"
				},
				"userId": "621b1ece9d0972037e04b7f3"
			}
			```
		- Falha
			```javascript
			HTTP/1.1 400 Bad Request
			```
			`Dado invalido`
			```javascript
			{
				"error": "Invalid dice!"
			}
			```
			`input invalido`
			```javascript
			{
				"error": "Invalid input!"
			}
			```
- # `GET /roll`

	`Obtém a lista de todas as jogadas feitas.`

		GET http://localhost:80/roll
		Authorization: Bearer <TOKEN>

	- ### Resposta
    	- Sucesso

			```javascript
			HTTP/1.1 200 OK
			```
			```javascript
			{
				"roll": {
					"_id": {
						"$oid": "621b1f0c9d0972037e04b7f4"
					},
					"date": {
						"$date": {
							"$numberLong": "1645944588803"
						}
					},
					"result": {
						"$numberInt": "1"
					},
					"userId": "621b1ece9d0972037e04b7f3"
				},
				...
			}
			```
- # `GET /roll:id`

	`Obtém as informações de uma jogada.`

		GET http://localhost:80/roll/:id
		Authorization: Bearer <TOKEN>

	- ### Resposta
    	- Sucesso

			```javascript
			HTTP/1.1 200 OK
			```
			```javascript
			{
				"roll": {
					"_id": {
						"$oid": "621b1f0c9d0972037e04b7f4"
					},
					"date": {
						"$date": {
							"$numberLong": "1645944588803"
						}
					},
					"result": {
						"$numberInt": "1"
					},
					"userId": "621b1ece9d0972037e04b7f3"
				}
			}

			```
- # `Delete /roll:id`

	`Apaga o registro de uma jogada.`

		DELETE http://localhost:80/roll/:id
		Authorization: Bearer <TOKEN>

    - ### Resposta
      - Sucesso

		```javascript
		HTTP/1.1 200 OK
		```
		```javascript
		{
			"ok": "Roll deleted!"
		}
		```