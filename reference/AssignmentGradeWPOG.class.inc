<?php
/*
	This SQL query will create the table to store your object. GEN FILE:/var/www/wings/pog/object_factory/class.objectphp5.1pdomysql.php

	CREATE TABLE `assignmentgrade` (
	`assignment_id` int(11) NOT NULL auto_increment,
	`assignment_id` INT NOT NULL,
	`student_id` INT NOT NULL,
	`points` INT NOT NULL,
	`grade_id` VARCHAR(255) NOT NULL,
	`comment` TINYINT NOT NULL,
	`is_waived` DATE NOT NULL,
	`due` DATE NOT NULL,
	`assigned`  NOT NULL, PRIMARY KEY  (`assignmentgradeid`)) ENGINE=MyISAM;
*/

/**
 * <b>AssignmentGrade</b> class with integrated CRUD methods.
 * @author Php Object Generator
 * @version POG 3.3 / PHP5.1 MYSQL
 * @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
 * @copyright Free for personal & commercial use. (Offered under the BSD license)
 * @link https://wingsdev.local/wings/pog/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=AssignmentGrade&attributeList=array+%28%0A++0+%3D%3E+%27assignment_id%27%2C%0A++1+%3D%3E+%27student_id%27%2C%0A++2+%3D%3E+%27points%27%2C%0A++3+%3D%3E+%27grade_id%27%2C%0A++4+%3D%3E+%27comment%27%2C%0A++5+%3D%3E+%27is_waived%27%2C%0A++6+%3D%3E+%27due%27%2C%0A++7+%3D%3E+%27assigned%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527TINYINT%2527%252C%250A%2B%2B6%2B%253D%253E%2B%2527DATE%2527%252C%250A%2B%2B7%2B%253D%253E%2B%2527DATE%2527%252C%250A%2529&classList=array+%28%0A++0+%3D%3E+%27%27%2C%0A++1+%3D%3E+%27%27%2C%0A++2+%3D%3E+%27%27%2C%0A++3+%3D%3E+%27%27%2C%0A++4+%3D%3E+%27%27%2C%0A++5+%3D%3E+%27%27%2C%0A++6+%3D%3E+%27%27%2C%0A++7+%3D%3E+%27%27%2C%0A%29
 */
require_once('WPOGBase.class.inc');
class AssignmentGrade extends WPOGBase
{
	public $assignmentgradeId = '';

	/**
	 * @var INT
	 */
	public $assignment_id;
	
	/**
	 * @var INT
	 */
	public $student_id;
	
	/**
	 * @var INT
	 */
	public $points;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $grade_id;
	
	/**
	 * @var TINYINT
	 */
	public $comment;
	
	/**
	 * @var DATE
	 */
	public $is_waived;
	
	/**
	 * @var DATE
	 */
	public $due;
	
	/**
	 * @var 
	 */
	public $assigned;
	
	public $pog_attribute_type = array(
		"assignment_id" => array('db_attributes' => array("NUMERIC", "INT")),
		"assignment_id" => array('db_attributes' => array("NUMERIC", "INT")),
		"student_id" => array('db_attributes' => array("NUMERIC", "INT")),
		"points" => array('db_attributes' => array("NUMERIC", "INT")),
		"grade_id" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"comment" => array('db_attributes' => array("NUMERIC", "TINYINT")),
		"is_waived" => array('db_attributes' => array("NUMERIC", "DATE")),
		"due" => array('db_attributes' => array("NUMERIC", "DATE")),
		"assigned" => array('db_attributes' => array("TEXT", "")),
		);
	public $pog_query;
	protected $connection;
	
	
	/**
	 * Getter for some private attributes
	 * @return mixed $attribute
	 */
	public function __get($attribute)
	{
		if (isset($this->{"_".$attribute})) {
			return $this->{"_".$attribute};
		} else {
			return false;
		}
	}
	
	function AssignmentGrade($assignment_id='', $student_id='', $points='', $grade_id='', $comment='', $is_waived='', $due='', $assigned='')
	{
		global $DATABASEPDO;
		$this->connection = $DATABASEPDO;
		$this->assignment_id = $assignment_id;
		$this->student_id = $student_id;
		$this->points = $points;
		$this->grade_id = $grade_id;
		$this->comment = $comment;
		$this->is_waived = $is_waived;
		$this->due = $due;
		$this->assigned = $assigned;
	}
	
	
	/**
	 * Gets object from database
	 * @param integer $assignment_id 
	 * @return object $AssignmentGrade
	 */
	function get($assignment_id)
	{
		$this->pog_query = "select * from `assignmentgrade` where `assignment_id`='".intval($assignment_id)."' LIMIT 1";
		$this->attributeList[0] = (int) $this->attributeList[0];
		if ( $this->attributeList[0] == 0 ) {
		throw new Exception( __FILE__ ." : ".  __LINE__ ." : Invalid ID: $this->attributeList[0].");
		}

		if ( 0 == Database::Query($this->pog_query, $this->connection) ) {
			throw new Exception( __FILE__ ." : ".  __LINE__ ." : Query ". $this->pog_query ."  failed. Is the table is empty?");
		}

		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor)) {
			$this->assignment_id = $this->Unescape($row['assignment_id']);
			$this->student_id = $this->Unescape($row['student_id']);
			$this->points = $this->Unescape($row['points']);
			$this->grade_id = $this->Unescape($row['grade_id']);
			$this->comment = $this->Unescape($row['comment']);
			$this->is_waived = $this->Unescape($row['is_waived']);
			$this->due = $row['due'];
			$this->assigned = $row['assigned'];
		}
		return $this;
	}
	
	
	/**
	 * Moved. Use collection object class instead.
	 * @return null
	 */
	//function getList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	//{
	//}
	
	
	/**
	 * Saves the object to the database
	 * @return integer $assignmentgradeId
	 */
	function save()
	{
		$rows = 0;
		if ($this->assignment_id!=''){
			$this->pog_query = "select `assignment_id` from `assignmentgrade` where `assignmentgradeid`='".$this->assignment_id."' LIMIT 1";
			$rows = Database::Query($this->pog_query, $connection);
		}
		if ($rows > 0) {
			$this->pog_query = "update `assignmentgrade` set 
				`assignment_id`='".$this->Escape($this->assignment_id)."', 
				`student_id`='".$this->Escape($this->student_id)."', 
				`points`='".$this->Escape($this->points)."', 
				`grade_id`='".$this->Escape($this->grade_id)."', 
				`comment`='".$this->Escape($this->comment)."', 
				`is_waived`='".$this->is_waived."', 
				`due`='".$this->due."' 
				`assigned`='".$this->Escape($this->assigned)."'where `assignment_id`='".$this->assignment_id."'";
		} else {
			$this->pog_query = "insert into `assignmentgrade` (`assignment_id`, `student_id`, `points`, `grade_id`, `comment`, `is_waived`, `due`, `assigned` ) values (
			'".$this->Escape($this->assignment_id)."', 
			'".$this->Escape($this->student_id)."', 
			'".$this->Escape($this->points)."', 
			'".$this->Escape($this->grade_id)."', 
			'".$this->Escape($this->comment)."', 
			'".$this->Escape($this->is_waived)."', 
			'".$this->due."', 
			'".$this->assigned."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->assignment_id == "") {
			$this->assignment_id = $insertId;
		}
		return $this->assignment_id;
	}
	
	
	/**
	 * Clones the object and saves it to the database
	 * @return integer $assignment_id
	 */
	function saveNew()
	{
		$this->assignment_id = '';
		return $this->save();
	}
	
	
	/**
	 * Deletes the object from the database
	 * @return boolean
	 */
	function delete()
	{
		$this->pog_query = "delete from `assignmentgrade` where `assignmentgradeid`='".$this->assignment_id."'";
		return Database::NonQuery($this->pog_query, $connection);
	}
	
	
	/**
	 * Moved. Use collection object class instead.
	 * @return null
	 */
	//function deleteList($fcv_array)
	//{
	//}
}
?>