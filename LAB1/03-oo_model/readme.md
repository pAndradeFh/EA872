Autor: Paulo Andrade, RA156951 |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Rotina para simulação de objeto acoplado uma mola, com resistência do ar

Adicionados
	campos do objeto: aceleracao, resistencia do ar e constante de mola
	métodos: get_aceleracao, get_amortecimento, get_constante_mola
Justificativa
	a aceleracao deve ser guardada para calculo da velocidade por integração
	a resistencia do ar pode ser indivizualizada para cada objeto
	idem para a constante de mola fixada em cada objeto
Refatorado
	Fisica: a função para calculo da posicao no delta t foi modificada para o problema
