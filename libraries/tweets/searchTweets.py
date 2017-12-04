import tweepy
import sys

##
# Autor: Alexandre Yuji Kajihara
# Descricao: utilizamos uma API do twitter utilizando a linguagem de programacao python
# para pegar os tweets sobre um determinado assunto.
# Data de criacao: 24/11/2017
# Data de atualizacao: 24/11/2017
##

##
# Este metodo recebe um parametro que e o assunto que o mesmo deseja pesquisar. 
# Com o assunto definido imprimimos na tela informacoes dos tweet no formato de um arquivo json.
# Imprimimos todos os tweets que sao permitidos pelo Twitter, que sao 3200 tweets.
# @param topic, que e o topico que se deseja pesquisar.
# @return nada, nao retorna nada.
##
def allTweets(topic):
	#Precisa fazer o cadastro no twitter como developer para conseguir essas chaves
	consumer_key = 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXX'
	consumer_secret = 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXX'
	access_token = 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXX'
	access_token_secret = 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXX'

	#Autenticacao
	auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
	auth.set_access_token(access_token, access_token_secret)
	api = tweepy.API(auth)

	#O twitter so permite 200 tweets, mas utilizando o Cursor voce pega 3200
	#Cada pagina tem 200, e temos 16 paginas entao 200 x 16 = 3200
	for i in range(1, 17):
		for tweet in tweepy.Cursor(api.search, q=topic, count=200).pages(i):
			print tweet

#Funcao main 
if __name__ == '__main__':
	#Verfica se foram passados dois parametros
    if len(sys.argv) == 2:
		allTweets(sys.argv[1])
    else:
		print("use: python %s assuntoPesquisa" % sys.argv[0])