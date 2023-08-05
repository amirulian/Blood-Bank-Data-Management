-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 15, 2022 at 03:15 AM
-- Server version: 10.4.21-MariaDB
-- PHP Version: 8.0.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `bloodbankmanagement`
--
CREATE DATABASE IF NOT EXISTS `bloodbankmanagement` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `bloodbankmanagement`;

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

DROP TABLE IF EXISTS `admin`;
CREATE TABLE IF NOT EXISTS `admin` (
  `Number` int(255) NOT NULL AUTO_INCREMENT,
  `adminid` varchar(10) NOT NULL,
  `email` varchar(30) NOT NULL,
  `name` varchar(30) NOT NULL,
  `accountid` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`adminid`),
  UNIQUE KEY `Number` (`Number`),
  KEY `email` (`email`),
  KEY `accountid` (`accountid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `blooddonated`
--

DROP TABLE IF EXISTS `blooddonated`;
CREATE TABLE IF NOT EXISTS `blooddonated` (
  `number` int(255) NOT NULL AUTO_INCREMENT,
  `donatedid` varchar(10) NOT NULL,
  `donorid` varchar(10) NOT NULL,
  `datein` DATE DEFAULT CURRENT_TIMESTAMP,
  `BloodType` varchar(3) NOT NULL,
  `WorkerID` varchar(10) DEFAULT NULL,
  `AdminID` varchar(10) DEFAULT NULL,
  `status` varchar(30) NOT NULL,
  `Disorder_Type` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`donatedid`),
  UNIQUE KEY `number` (`number`),
  KEY `WorkerID` (`WorkerID`),
  KEY `AdminID` (`AdminID`),
  KEY `donorid` (`donorid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `bloodstock`
--

DROP TABLE IF EXISTS `bloodstock`;
CREATE TABLE IF NOT EXISTS `bloodstock` (
  `Bloodtype` varchar(3) NOT NULL,
  `Quantity` int(255) NOT NULL,
  PRIMARY KEY (`Bloodtype`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `donor`
--

DROP TABLE IF EXISTS `donor`;
CREATE TABLE IF NOT EXISTS `donor` (
  `number` int(11) NOT NULL AUTO_INCREMENT,
  `DonorID` varchar(10) NOT NULL,
  `Name` varchar(30) NOT NULL,
  `ContactNumber` varchar(30) NOT NULL,
  `BloodType` varchar(3) NOT NULL,
  `IDCardNumber` varchar(17) NOT NULL,
  `WorkerID` varchar(10) DEFAULT NULL,
  `adminID` varchar(10) DEFAULT NULL,
  `PPDID` varchar(10) NOT NULL,
  PRIMARY KEY (`DonorID`),
  UNIQUE KEY `number` (`number`),
  UNIQUE KEY `IDCardNumber` (`IDCardNumber`),
  KEY `adminID` (`adminID`),
  KEY `WorkerID` (`WorkerID`),
  KEY `PPDID` (`PPDID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `hospital`
--

DROP TABLE IF EXISTS `hospital`;
CREATE TABLE IF NOT EXISTS `hospital` (
  `HospitalID` varchar(10) NOT NULL,
  `Name` varchar(100) NOT NULL,
  `Address` varchar(100) NOT NULL,
  PRIMARY KEY (`HospitalID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `logindetail`
--

DROP TABLE IF EXISTS `logindetail`;
CREATE TABLE IF NOT EXISTS `logindetail` (
  `Number` int(255) NOT NULL AUTO_INCREMENT,
  `accountid` varchar(20) NOT NULL,
  `name` varchar(30) NOT NULL,
  `email` varchar(30) NOT NULL,
  `password` varchar(255) NOT NULL,
  PRIMARY KEY (`accountid`),
  UNIQUE KEY `Number` (`Number`),
  UNIQUE KEY `email` (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `orderblood`
--

DROP TABLE IF EXISTS `orderblood`;
CREATE TABLE IF NOT EXISTS `orderblood` (
  `number` int(11) NOT NULL AUTO_INCREMENT,
  `sentoutInvoiceid` varchar(10) NOT NULL,
  `receivedrequestInvoiceID` varchar(10) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `quantity` int(11) NOT NULL,
  `DateOut` date DEFAULT current_timestamp(),
  `HospitalID` varchar(10) NOT NULL,
  PRIMARY KEY (`sentoutInvoiceid`),
  UNIQUE KEY `receivedrequestInvoiceID` (`receivedrequestInvoiceID`),
  UNIQUE KEY `number` (`number`),
  KEY `HospitalID` (`HospitalID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `pusatdermadarah`
--

DROP TABLE IF EXISTS `pusatdermadarah`;
CREATE TABLE IF NOT EXISTS `pusatdermadarah` (
  `PPDID` varchar(10) NOT NULL,
  `Name` varchar(100) NOT NULL,
  `Address` varchar(100) NOT NULL,
  PRIMARY KEY (`PPDID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `worker`
--

DROP TABLE IF EXISTS `worker`;
CREATE TABLE IF NOT EXISTS `worker` (
  `Number` int(255) NOT NULL AUTO_INCREMENT,
  `workerid` varchar(10) NOT NULL,
  `name` varchar(30) NOT NULL,
  `email` varchar(30) NOT NULL,
  `homeaddress` varchar(255) NOT NULL,
  `mailingaddress` varchar(255) NOT NULL,
  `idcardnumber` varchar(100) NOT NULL,
  `accountid` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`workerid`),
  UNIQUE KEY `Number` (`Number`),
  UNIQUE KEY `idcardnumber` (`idcardnumber`),
  KEY `email` (`email`),
  KEY `accountid` (`accountid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `admin`
--
ALTER TABLE `admin`
  ADD CONSTRAINT `admin_ibfk_1` FOREIGN KEY (`email`) REFERENCES `logindetail` (`email`),
  ADD CONSTRAINT `admin_ibfk_2` FOREIGN KEY (`accountid`) REFERENCES `logindetail` (`accountid`);

--
-- Constraints for table `blooddonated`
--
ALTER TABLE `blooddonated`
  ADD CONSTRAINT `blooddonated_ibfk_1` FOREIGN KEY (`WorkerID`) REFERENCES `worker` (`workerid`),
  ADD CONSTRAINT `blooddonated_ibfk_2` FOREIGN KEY (`AdminID`) REFERENCES `admin` (`adminid`),
  ADD CONSTRAINT `blooddonated_ibfk_3` FOREIGN KEY (`donorid`) REFERENCES `donor` (`DonorID`);

--
-- Constraints for table `donor`
--
ALTER TABLE `donor`
  ADD CONSTRAINT `donor_ibfk_1` FOREIGN KEY (`adminID`) REFERENCES `admin` (`adminid`),
  ADD CONSTRAINT `donor_ibfk_2` FOREIGN KEY (`WorkerID`) REFERENCES `worker` (`workerid`),
  ADD CONSTRAINT `donor_ibfk_3` FOREIGN KEY (`PPDID`) REFERENCES `pusatdermadarah` (`PPDID`);

--
-- Constraints for table `orderblood`
--
ALTER TABLE `orderblood`
  ADD CONSTRAINT `orderblood_ibfk_1` FOREIGN KEY (`HospitalID`) REFERENCES `hospital` (`HospitalID`);

--
-- Constraints for table `worker`
--
ALTER TABLE `worker`
  ADD CONSTRAINT `worker_ibfk_1` FOREIGN KEY (`email`) REFERENCES `logindetail` (`email`),
  ADD CONSTRAINT `worker_ibfk_2` FOREIGN KEY (`accountid`) REFERENCES `logindetail` (`accountid`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
