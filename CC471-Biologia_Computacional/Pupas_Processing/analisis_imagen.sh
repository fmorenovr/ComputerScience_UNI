#!usr/bin/bash

echo "G1 antes ... "
python analisis_colores.py pupas_foto/G1_antes.png > resultado_g1_antes.html

echo "G1 despues ... " 
python analisis_colores.py pupas_foto/G1_despues.png > resultado_g1_despues.html

echo "G2 antes ... "
python analisis_colores.py pupas_foto/G2_antes.png > resultado_g2_antes.html

echo "G2 despues ... " 
python analisis_colores.py pupas_foto/G2_despues.png > resultado_g2_despues.html 

