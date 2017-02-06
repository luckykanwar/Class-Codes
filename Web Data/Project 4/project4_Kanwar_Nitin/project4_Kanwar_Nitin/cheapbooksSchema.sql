CREATE DATABASE  IF NOT EXISTS `cheapbook` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `cheapbook`;
-- MySQL dump 10.13  Distrib 5.7.16, for Linux (i686)
--
-- Host: localhost    Database: cheapbook
-- ------------------------------------------------------
-- Server version	5.7.16-0ubuntu0.16.10.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `author`
--

DROP TABLE IF EXISTS `author`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `author` (
  `ssn` varchar(20) NOT NULL,
  `name` varchar(100) DEFAULT NULL,
  `address` varchar(100) DEFAULT NULL,
  `phone` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`ssn`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `author`
--

LOCK TABLES `author` WRITE;
/*!40000 ALTER TABLE `author` DISABLE KEYS */;
INSERT INTO `author` VALUES ('1234ABCDE','Dan Brown','Exeter, New Hampshire','6827169118'),('1234ABCDF','Jeffrey Archer','London, United Kingdom','6827169119'),('1234ABCDG','Khaled Hosseini','Kabul, Afghanistan','6827169120'),('1234ABCDH','Ayn Rand','New York City, New York','6827169121');
/*!40000 ALTER TABLE `author` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `book`
--

DROP TABLE IF EXISTS `book`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `book` (
  `isbn` varchar(20) NOT NULL,
  `title` varchar(100) DEFAULT NULL,
  `year` int(11) DEFAULT NULL,
  `price` decimal(4,2) DEFAULT NULL,
  `publisher` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`isbn`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `book`
--

LOCK TABLES `book` WRITE;
/*!40000 ALTER TABLE `book` DISABLE KEYS */;
INSERT INTO `book` VALUES ('0-312-18087-X','Digital Fortress',1998,10.50,'St. Martins Press Transworld'),('0-340-24594-8','Kane and Abel',1979,13.49,'Hodder & Stoughton'),('0-385-50420-9','Da Vinci Code',2003,13.00,'Double Day'),('0-671-02735-2','Angels and Demons',2000,12.99,'Corgi Books'),('0-671-02738-7','Deception Point',2001,11.75,'Pocket Books'),('1-57322-245-3','The Kite Runner',2003,12.00,'Riverhead Books'),('300033023','The Fountainhead',1943,25.00,'Bobbs Merrill'),('412355486','Atlas Shrugged',1957,20.00,'Random House'),('978-0-312-53951-1','Paths of Glory',2009,15.00,'St. Martins Press'),('978-1-59448-950-1','A Thousand Splendid Suns',2007,15.00,'Riverhead Books');
/*!40000 ALTER TABLE `book` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `contains`
--

DROP TABLE IF EXISTS `contains`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `contains` (
  `isbn` varchar(20) NOT NULL,
  `basketid` int(11) NOT NULL,
  `number` int(11) DEFAULT NULL,
  `warehousecode` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`isbn`,`basketid`),
  KEY `basketid` (`basketid`),
  KEY `warehousecode` (`warehousecode`),
  CONSTRAINT `contains_ibfk_1` FOREIGN KEY (`isbn`) REFERENCES `book` (`isbn`),
  CONSTRAINT `contains_ibfk_2` FOREIGN KEY (`basketid`) REFERENCES `shoppingbasket` (`basketid`),
  CONSTRAINT `contains_ibfk_3` FOREIGN KEY (`warehousecode`) REFERENCES `warehouse` (`warehousecode`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `contains`
--

LOCK TABLES `contains` WRITE;
/*!40000 ALTER TABLE `contains` DISABLE KEYS */;
/*!40000 ALTER TABLE `contains` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customers`
--

DROP TABLE IF EXISTS `customers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `customers` (
  `username` varchar(10) NOT NULL,
  `password` varchar(32) DEFAULT NULL,
  `address` varchar(100) DEFAULT NULL,
  `phone` varchar(20) DEFAULT NULL,
  `email` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customers`
--

LOCK TABLES `customers` WRITE;
/*!40000 ALTER TABLE `customers` DISABLE KEYS */;
INSERT INTO `customers` VALUES ('dada','b01abf84324066bdb4eed4d5bf20f887','dada','dad','dada'),('dadad','df3939f11965e7e75dbc046cd9af1c67','adad','adad','adad'),('dadada','7627cb9027e713e301e83a8f13057055','dadadad','dadadad','dadadad'),('dadadadad','7ea97fa5c1534cd91fe666690a60e927','dadadadad','dadadadad','dadadadad'),('hellohello','23b431acfeb41e15d466d75de822307c','hellohello','hellohello','hellohello'),('Kanwar','f4d61f37a65be25d9a7491d19d4ef101','Arlington','6828123953','kanwar@gmail.com'),('kkkkkkkk','78d1fe0f0064cf6654940c87d99d4456','kkkkkkkk','kkkkkkkk','kkkkkkkk'),('kunwar','e77989ed21758e78331b20e477fc5582','arlington','13632566354','kds@gmail.com'),('lucky','f4d61f37a65be25d9a7491d19d4ef101','Arlington','1234567890','luckykanwar@gmail.com'),('lucky1','c753c2f24e0281b48126e2df709b22e4','jkfahf','fjkajfha','jkfahf'),('nitin','dacaba0bcef349afbb0441bfb5d13f8f','Arlington, Texas','6827169008','luckykanwar@gmail.com'),('nitin1','dacaba0bcef349afbb0441bfb5d13f8f','Aprt 129, 1006 Greek Row Drive, Arlington','6827169008','luckykanwar@gmail.com'),('nitin2','dacaba0bcef349afbb0441bfb5d13f8f','Aprt 129, 1006 Greek Row Drive, Arlington','6827169008','luckykanwar@gmail.com'),('nitin3','1234','123','234','luc'),('register','085ac036b69d08e08650e21c10bce3b2','register','register','register'),('sharm','6ab80775c661f7210e4af5a48496f3ed','dafhghagf','fhafhagfhagfgh','shahdha'),('swati','f823937995b27ffcbf668da4a22d5bd3','swati','swati','swati'),('test','d41d8cd98f00b204e9800998ecf8427e','tes','555','5555'),('testttt','d41d8cd98f00b204e9800998ecf8427e','ttt','tt','ttt'),('yello','c61dd29d8ca0b9811053d909ce7b0c6f','yello','yello','yello');
/*!40000 ALTER TABLE `customers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `shippingorder`
--

DROP TABLE IF EXISTS `shippingorder`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `shippingorder` (
  `shippingid` int(11) NOT NULL AUTO_INCREMENT,
  `isbn` varchar(20) NOT NULL,
  `warehousecode` varchar(20) NOT NULL,
  `username` varchar(10) NOT NULL,
  `number` int(11) DEFAULT NULL,
  PRIMARY KEY (`shippingid`,`isbn`,`warehousecode`,`username`),
  KEY `warehousecode` (`warehousecode`),
  KEY `username` (`username`),
  KEY `shippingorder_ibfk_2` (`isbn`),
  CONSTRAINT `shippingorder_ibfk_1` FOREIGN KEY (`warehousecode`) REFERENCES `warehouse` (`warehousecode`),
  CONSTRAINT `shippingorder_ibfk_2` FOREIGN KEY (`isbn`) REFERENCES `book` (`isbn`),
  CONSTRAINT `shippingorder_ibfk_3` FOREIGN KEY (`username`) REFERENCES `customers` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shippingorder`
--

LOCK TABLES `shippingorder` WRITE;
/*!40000 ALTER TABLE `shippingorder` DISABLE KEYS */;
INSERT INTO `shippingorder` VALUES (33,'0-671-02735-2','123456789','lucky',1),(34,'1-57322-245-3','987654321','lucky',1),(35,'0-671-02735-2','123456789','lucky',22),(36,'1-57322-245-3','987654321','lucky',1),(37,'412355486','987654321','dadadadad',1),(38,'0-671-02738-7','123456789','swati',1),(39,'1-57322-245-3','987654321','swati',2);
/*!40000 ALTER TABLE `shippingorder` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `shoppingbasket`
--

DROP TABLE IF EXISTS `shoppingbasket`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `shoppingbasket` (
  `basketid` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`basketid`),
  KEY `username` (`username`),
  CONSTRAINT `shoppingbasket_ibfk_1` FOREIGN KEY (`username`) REFERENCES `customers` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=136 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shoppingbasket`
--

LOCK TABLES `shoppingbasket` WRITE;
/*!40000 ALTER TABLE `shoppingbasket` DISABLE KEYS */;
INSERT INTO `shoppingbasket` VALUES (117,'dada'),(133,'dadadadad'),(114,'lucky'),(118,'lucky'),(119,'lucky'),(120,'lucky'),(121,'lucky'),(122,'lucky'),(123,'lucky'),(124,'lucky'),(125,'lucky'),(126,'lucky'),(127,'lucky'),(128,'lucky'),(129,'lucky'),(130,'lucky'),(131,'lucky'),(132,'lucky'),(134,'swati'),(135,'swati'),(116,'yello');
/*!40000 ALTER TABLE `shoppingbasket` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stocks`
--

DROP TABLE IF EXISTS `stocks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stocks` (
  `isbn` varchar(20) NOT NULL,
  `warehousecode` varchar(20) NOT NULL,
  `number` int(11) DEFAULT NULL,
  PRIMARY KEY (`isbn`,`warehousecode`),
  KEY `warehousecode` (`warehousecode`),
  CONSTRAINT `stocks_ibfk_1` FOREIGN KEY (`isbn`) REFERENCES `book` (`isbn`),
  CONSTRAINT `stocks_ibfk_2` FOREIGN KEY (`warehousecode`) REFERENCES `warehouse` (`warehousecode`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stocks`
--

LOCK TABLES `stocks` WRITE;
/*!40000 ALTER TABLE `stocks` DISABLE KEYS */;
INSERT INTO `stocks` VALUES ('0-312-18087-X','123456789',97),('0-312-18087-X','123654789',67),('0-312-18087-X','987654321',59),('0-385-50420-9','123456789',49),('0-671-02735-2','123456789',33),('0-671-02738-7','123456789',59),('1-57322-245-3','987654321',62),('300033023','987654321',73),('412355486','987654321',88),('978-0-312-53951-1','123456789',50),('978-1-59448-950-1','123456789',10);
/*!40000 ALTER TABLE `stocks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `warehouse`
--

DROP TABLE IF EXISTS `warehouse`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `warehouse` (
  `warehousecode` varchar(20) NOT NULL,
  `name` varchar(100) DEFAULT NULL,
  `address` varchar(100) DEFAULT NULL,
  `phone` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`warehousecode`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `warehouse`
--

LOCK TABLES `warehouse` WRITE;
/*!40000 ALTER TABLE `warehouse` DISABLE KEYS */;
INSERT INTO `warehouse` VALUES ('123456789','Texas ','Arlington','8888888888'),('123654789','New York ','Buffalo','7777777777'),('987654321','California ','San Diego','9999999999');
/*!40000 ALTER TABLE `warehouse` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `writtenby`
--

DROP TABLE IF EXISTS `writtenby`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `writtenby` (
  `ssn` varchar(20) NOT NULL,
  `isbn` varchar(20) NOT NULL,
  PRIMARY KEY (`ssn`,`isbn`),
  KEY `isbn` (`isbn`),
  CONSTRAINT `writtenby_ibfk_1` FOREIGN KEY (`ssn`) REFERENCES `author` (`ssn`),
  CONSTRAINT `writtenby_ibfk_2` FOREIGN KEY (`isbn`) REFERENCES `book` (`isbn`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `writtenby`
--

LOCK TABLES `writtenby` WRITE;
/*!40000 ALTER TABLE `writtenby` DISABLE KEYS */;
INSERT INTO `writtenby` VALUES ('1234ABCDE','0-312-18087-X'),('1234ABCDF','0-340-24594-8'),('1234ABCDE','0-385-50420-9'),('1234ABCDE','0-671-02735-2'),('1234ABCDE','0-671-02738-7'),('1234ABCDG','1-57322-245-3'),('1234ABCDH','300033023'),('1234ABCDH','412355486'),('1234ABCDF','978-0-312-53951-1'),('1234ABCDG','978-1-59448-950-1');
/*!40000 ALTER TABLE `writtenby` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-11-30 18:45:56
