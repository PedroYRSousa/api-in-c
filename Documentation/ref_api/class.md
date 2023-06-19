# Rotas de Class

- # `GET /class`

	`Obtém a lista de todas as classes disponíveis.`

		GET http://localhost:80/class

	- ### Resposta
    	- Sucesso

			```javascript
			HTTP/1.1 200 OK
			```
			```javascript
			{
				"class": {
					"_id": {
						"$oid": "621995e2766303022f3c320d"
					},
					"name": "Barbarian"
				},
				...
			}
			```
- # `GET /class:id`

	`Obtém as informações de uma classe.`

		GET http://localhost:80/class/:id

	- ### Resposta
    	- Sucesso

			```javascript
			HTTP/1.1 200 OK
			```
			```javascript
			{
				"class": {
					"_id": {
						"$oid": "621995e2766303022f3c320d"
					},
					"name": "Barbarian"
				}
			}
			```