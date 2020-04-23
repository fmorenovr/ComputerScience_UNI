
-- phpMyAdmin SQL Dump
-- version 3.5.2.2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Dec 14, 2016 at 07:51 PM
-- Server version: 10.0.20-MariaDB
-- PHP Version: 5.2.17

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `u879094972_venta`
--

-- --------------------------------------------------------

--
-- Table structure for table `cliente`
--

CREATE TABLE IF NOT EXISTS `cliente` (
  `idc` int(3) NOT NULL AUTO_INCREMENT,
  `nombre` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `usuario` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `pass` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `rol` int(3) NOT NULL,
  PRIMARY KEY (`idc`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=8 ;

--
-- Dumping data for table `cliente`
--

INSERT INTO `cliente` (`idc`, `nombre`, `usuario`, `pass`, `rol`) VALUES
(1, 'Yuri', 'hacker', '123456', 0),
(2, 'juan ramirez', 'JuanR', '123456', 1),
(3, 'rosa rodriguez', 'Rosaa', '123456', 1),
(4, 'pepe gonzales', 'Pepon', '123456', 1),
(5, 'miriam gomez', 'Miri', '123456', 1),
(6, 'roberto wu', 'robertin', '123456', 1),
(7, 'super yuri', 'iOS_hacker', 'ios', 0);

-- --------------------------------------------------------

--
-- Table structure for table `detalle_recibo`
--

CREATE TABLE IF NOT EXISTS `detalle_recibo` (
  `iddr` int(3) NOT NULL,
  `idp` int(3) NOT NULL,
  `idr` int(3) NOT NULL,
  `idd` int(3) NOT NULL,
  PRIMARY KEY (`iddr`,`idp`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `detalle_recibo`
--

INSERT INTO `detalle_recibo` (`iddr`, `idp`, `idr`, `idd`) VALUES
(1, 2, 5, 0),
(1, 4, 10, 0),
(2, 3, 15, 0),
(2, 4, 5, 0),
(2, 5, 20, 0),
(3, 1, 5, 0),
(4, 2, 20, 0);

-- --------------------------------------------------------

--
-- Table structure for table `producto`
--

CREATE TABLE IF NOT EXISTS `producto` (
  `idp` int(3) NOT NULL AUTO_INCREMENT,
  `nomp` varchar(70) COLLATE utf8_unicode_ci DEFAULT NULL,
  `prep` float NOT NULL,
  `cantp` int(10) NOT NULL,
  PRIMARY KEY (`idp`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=6 ;

--
-- Dumping data for table `producto`
--

INSERT INTO `producto` (`idp`, `nomp`, `prep`, `cantp`) VALUES
(1, 'MEMORIA USB 2.0 64GB KINGSTON DT100G3', 25, 15),
(2, 'MEMORIA USB 3.0 8GB KINGSTON DTSE9G2', 22, 50),
(3, 'MEMORIA USB 8GB KINGSTON DTS6', 26, 65),
(4, 'MEMORIA USB 8GB PATRIOT AXLE Mini', 21, 35),
(5, 'MEMORIA USB 8GB KINGSTON KC-U468', 23, 80);

-- --------------------------------------------------------

--
-- Table structure for table `recibo`
--

CREATE TABLE IF NOT EXISTS `recibo` (
  `idr` int(3) NOT NULL AUTO_INCREMENT,
  `idc` int(3) DEFAULT NULL,
  `total` float DEFAULT NULL,
  `idcodbanco` int(4) NOT NULL,
  `estado` int(1) NOT NULL,
  PRIMARY KEY (`idr`),
  KEY `idc` (`idc`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=6 ;

--
-- Dumping data for table `recibo`
--

INSERT INTO `recibo` (`idr`, `idc`, `total`, `idcodbanco`, `estado`) VALUES
(1, 2, 320, 5001, 1),
(2, 3, 955, 9100, 2),
(3, 4, 125, 2002, 2),
(4, 5, 440, 0, 0),
(5, 6, 0, 0, 0);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
