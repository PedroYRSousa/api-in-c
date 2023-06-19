# Rotas de Race

- # `GET /race`

	`Obtém a lista de todas as raças disponíveis.`

		GET http://localhost:80/race

	- ### Resposta
    	- Sucesso

			```javascript
			HTTP/1.1 200 OK
			```
			```javascript
			{
				"race": {
					"_id": {
						"$oid": "62199672766303022f3c3231"
					},
					"name": "Dragonborn"
				},
				...
			}
			```
- # `GET /race:id`

	`Obtém as informações de uma raça.`

		GET http://localhost:80/race/:id

	- ### Resposta
    	- Sucesso

			```javascript
			HTTP/1.1 200 OK
			```
			```javascript
			{
				"race": {
					"_id": {
						"$oid": "62199672766303022f3c3231"
					},
					"name": "Dragonborn"
				}
			}
			```