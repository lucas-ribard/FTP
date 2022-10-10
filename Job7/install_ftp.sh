#installer proftpd openssl filezilla
sudo apt-get install proftpd-*
sudo apt-get install openssl
sudo apt-get install filezilla

#generer la clef ssl
sudo mkdir /etc/proftpd/ssl
sudo openssl req -x509 -newkey rsa:2048 -keyout /etc/proftpd/ssl/proftpd.key.pem -out /etc/proftpd/ssl/proftpd.cert.pem -nodes -days 365

#remplacer les fichier de confs
sudo cp modules.conf /etc/proftpd/modules.conf
sudo cp proftpd.conf /etc/proftpd/proftpd.conf
sudo cp tls.conf /etc/proftpd/tls.conf

#actualiser proftpd
sudo ystemctl restart proftpd

#creer merry
sudo useradd pippin
sudo passwd merry << EOD
kalimac
kalimac
EOD
#creer pippin
sudo useradd pippin
sudo passwd pippin << EOD
secondbreakfast
secondbreakfast
EOD

