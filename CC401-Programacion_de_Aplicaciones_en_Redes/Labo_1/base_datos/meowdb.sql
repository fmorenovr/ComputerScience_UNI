-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 18-05-2016 a las 03:21:43
-- Versión del servidor: 5.6.17
-- Versión de PHP: 5.5.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de datos: `meowdb`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `usuarios`
--

CREATE TABLE IF NOT EXISTS `usuarios` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nombre` varchar(30) COLLATE utf8_spanish_ci DEFAULT NULL,
  `apellido` varchar(30) COLLATE utf8_spanish_ci DEFAULT NULL,
  `codigo` varchar(30) COLLATE utf8_spanish_ci DEFAULT NULL,
  `telefono` varchar(30) COLLATE utf8_spanish_ci DEFAULT NULL,
  `direccion` varchar(30) COLLATE utf8_spanish_ci DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci AUTO_INCREMENT=8 ;

--
-- Volcado de datos para la tabla `usuarios`
--

INSERT INTO `usuarios` (`id`, `nombre`, `apellido`, `codigo`, `telefono`, `direccion`) VALUES
(1, 'Felipe', 'Moreno', '123', '992654789', NULL),
(2, 'Kabrusto', 'Mamopecho', '456', '113456789', 'calle mamonidas 123'),
(3, 'LactayGuina', 'mamaranda', '456', '4567897', 'av el mamon 456'),
(4, 'Mamongasho', 'mamalpolo', '101', '548798546', 'Mamongasho 21244'),
(5, 'Chehco', 'gig', '486', '4513231', 'jr sucre'),
(6, 'Sotelo', 'Antaurco', NULL, '4578987', NULL),
(7, 'Adrian', 'Viera', '4564879798', '7897987987', 'jr areuqupa');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
