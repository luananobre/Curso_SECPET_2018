# Geofísica aplicada à sísmica de exploração

#### **IV Semana Científica do PET-Física - UFRRJ**

#### **Carlos Henrique e Luana Nobre**

## Pré-Requisitos

***
1.  Ambiente Linux e compilador para c

2. Software Seismic Unix

## Instruções para instalação do Software Seismic Unix

***

1. Faça o download utilizando o link <https://github.com/JohnWStockwellJr/SeisUnix>

2. Entre no arquivo `.bashrc` para definir o diretorio de instalação. 
	Acrescente as linhas a seguir:

	export CWPROOT=$HOME/SeisUnix
  
	export PATH=$CWPROOT/bin:$PATH

3. carregue as novas variáveis:
  
	source $HOME/.bashrc

4. crie uma pasta onde deseja que seja instalado o seimsic unix: 

	  mkdir cwp

5. Mova o arquivo .zip para a pasta SeisUnix e o renomeie como SeisUnix

6. Descompacte o arquivo:

    unzip SeisUnix-master.zip
	
7. entre na pasta SeisUnix-master/src e comente a linha no arquivo `Makefile.config`

	  "XDRFLAG = -DSUXDR" 
	
8. Execute e siga os passos da instalação

    make install

9. Após finalizado, execute:

    make xtinstall

10. teste a instalação com o comando:

	suplane | suximage title="My First Plot"
