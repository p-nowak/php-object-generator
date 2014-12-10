<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `assignmentgrade` (
	`assignmentgradeid` int(11) NOT NULL auto_increment,
	`assignment_id` INT NOT NULL,
	`student_id` INT NOT NULL,
	`points` INT NOT NULL,
	`grade_id` INT NOT NULL,
	`comment` VARCHAR(255) NOT NULL,
	`is_waived` TINYINT NOT NULL,
	`due` DATE NOT NULL,
	`assigned` DATE NOT NULL, PRIMARY KEY  (`assignmentgradeid`)) ENGINE=MyISAM;
*/

/**
* <b>AssignmentGrade</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.3 / PHP5.1 MYSQL
* @see http://www.phpobjectgenerator.com/plog/tutorials/45/pdo-mysql
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link https://wingsdev.local/wings/pog/?language=php5.1&wrapper=pdo&pdoDriver=mysql&objectName=AssignmentGrade&attributeList=array+%28%0A++0+%3D%3E+%27assignment_id%27%2C%0A++1+%3D%3E+%27student_id%27%2C%0A++2+%3D%3E+%27points%27%2C%0A++3+%3D%3E+%27grade_id%27%2C%0A++4+%3D%3E+%27comment%27%2C%0A++5+%3D%3E+%27is_waived%27%2C%0A++6+%3D%3E+%27due%27%2C%0A++7+%3D%3E+%27assigned%27%2C%0A%29&typeList=array%2B%2528%250A%2B%2B0%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B1%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B2%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B3%2B%253D%253E%2B%2527INT%2527%252C%250A%2B%2B4%2B%253D%253E%2B%2527VARCHAR%2528255%2529%2527%252C%250A%2B%2B5%2B%253D%253E%2B%2527TINYINT%2527%252C%250A%2B%2B6%2B%253D%253E%2B%2527DATE%2527%252C%250A%2B%2B7%2B%253D%253E%2B%2527DATE%2527%252C%250A%2529&classList=array+%28%0A++0+%3D%3E+%27%27%2C%0A++1+%3D%3E+%27%27%2C%0A++2+%3D%3E+%27%27%2C%0A++3+%3D%3E+%27%27%2C%0A++4+%3D%3E+%27%27%2C%0A++5+%3D%3E+%27%27%2C%0A++6+%3D%3E+%27%27%2C%0A++7+%3D%3E+%27%27%2C%0A%29
*/
include_once('class.pog_base.php');
class AssignmentGrade extends POG_Base
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
	 * @var INT
	 */
	public $grade_id;
	
	/**
	 * @var VARCHAR(255)
	 */
	public $comment;
	
	/**
	 * @var TINYINT
	 */
	public $is_waived;
	
	/**
	 * @var DATE
	 */
	public $due;
	
	/**
	 * @var DATE
	 */
	public $assigned;
	
	public $pog_attribute_type = array(
		"assignmentgradeId" => array('db_attributes' => array("NUMERIC", "INT")),
		"assignment_id" => array('db_attributes' => array("NUMERIC", "INT")),
		"student_id" => array('db_attributes' => array("NUMERIC", "INT")),
		"points" => array('db_attributes' => array("NUMERIC", "INT")),
		"grade_id" => array('db_attributes' => array("NUMERIC", "INT")),
		"comment" => array('db_attributes' => array("TEXT", "VARCHAR", "255")),
		"is_waived" => array('db_attributes' => array("NUMERIC", "TINYINT")),
		"due" => array('db_attributes' => array("NUMERIC", "DATE")),
		"assigned" => array('db_attributes' => array("NUMERIC", "DATE")),
		);
	public $pog_query;
	
	
	/**
	* Getter for some private attributes
	* @return mixed $attribute
	*/
	public function __get($attribute)
	{
		if (isset($this->{"_".$attribute}))
		{
			return $this->{"_".$attribute};
		}
		else
		{
			return false;
		}
	}
	
	function AssignmentGrade($assignment_id='', $student_id='', $points='', $grade_id='', $comment='', $is_waived='', $due='', $assigned='')
	{
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
	* @param integer $assignmentgradeId 
	* @return object $AssignmentGrade
	*/
	function Get($assignmentgradeId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `assignmentgrade` where `assignmentgradeid`='".intval($assignmentgradeId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->assignmentgradeId = $row['assignmentgradeid'];
			$this->assignment_id = $this->unescape($row['assignment_id']);
			$this->student_id = $this->unescape($row['student_id']);
			$this->points = $this->unescape($row['points']);
			$this->grade_id = $this->unescape($row['grade_id']);
			$this->comment = $this->unescape($row['comment']);
			$this->is_waived = $this->unescape($row['is_waived']);
			$this->due = $row['due'];
			$this->assigned = $row['assigned'];
		}
		return $this;
	}
	
	
	/**
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $assignmentgradeList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `assignmentgrade` ";
		$assignmentgradeList = Array();
		if (sizeof($fcv_array) > 0)
		{
			$this->pog_query .= " where ";
			for ($i=0, $c=sizeof($fcv_array); $i<$c; $i++)
			{
				if (sizeof($fcv_array[$i]) == 1)
				{
					$this->pog_query .= " ".$fcv_array[$i][0]." ";
					continue;
				}
				else
				{
					if ($i > 0 && sizeof($fcv_array[$i-1]) != 1)
					{
						$this->pog_query .= " AND ";
					}
					if (isset($this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes']) && $this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'NUMERIC' && $this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'SET')
					{
						if ($GLOBALS['configuration']['db_encoding'] == 1)
						{
							$value = POG_Base::IsColumn($fcv_array[$i][2]) ? "BASE64_DECODE(".$fcv_array[$i][2].")" : "'".$fcv_array[$i][2]."'";
							$this->pog_query .= "BASE64_DECODE(`".$fcv_array[$i][0]."`) ".$fcv_array[$i][1]." ".$value;
						}
						else
						{
							$value =  POG_Base::IsColumn($fcv_array[$i][2]) ? $fcv_array[$i][2] : "'".$this->escape($fcv_array[$i][2])."'";
							$this->pog_query .= "`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." ".$value;
						}
					}
					else
					{
						$value = POG_Base::IsColumn($fcv_array[$i][2]) ? $fcv_array[$i][2] : "'".$fcv_array[$i][2]."'";
						$this->pog_query .= "`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." ".$value;
					}
				}
			}
		}
		if ($sortBy != '')
		{
			if (isset($this->pog_attribute_type[$sortBy]['db_attributes']) && $this->pog_attribute_type[$sortBy]['db_attributes'][0] != 'NUMERIC' && $this->pog_attribute_type[$sortBy]['db_attributes'][0] != 'SET')
			{
				if ($GLOBALS['configuration']['db_encoding'] == 1)
				{
					$sortBy = "BASE64_DECODE($sortBy) ";
				}
				else
				{
					$sortBy = "$sortBy ";
				}
			}
			else
			{
				$sortBy = "$sortBy ";
			}
		}
		else
		{
			$sortBy = "assignmentgradeid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$assignmentgrade = new $thisObjectName();
			$assignmentgrade->assignmentgradeId = $row['assignmentgradeid'];
			$assignmentgrade->assignment_id = $this->unescape($row['assignment_id']);
			$assignmentgrade->student_id = $this->unescape($row['student_id']);
			$assignmentgrade->points = $this->unescape($row['points']);
			$assignmentgrade->grade_id = $this->unescape($row['grade_id']);
			$assignmentgrade->comment = $this->unescape($row['comment']);
			$assignmentgrade->is_waived = $this->unescape($row['is_waived']);
			$assignmentgrade->due = $row['due'];
			$assignmentgrade->assigned = $row['assigned'];
			$assignmentgradeList[] = $assignmentgrade;
		}
		return $assignmentgradeList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $assignmentgradeId
	*/
	function save()
	{
		$connection = Database::Connect();
		$rows = 0;
		if ($this->assignmentgradeId!=''){
			$this->pog_query = "select `assignmentgradeid` from `assignmentgrade` where `assignmentgradeid`='".$this->assignmentgradeId."' LIMIT 1";
			$rows = Database::Query($this->pog_query, $connection);
		}
		if ($rows > 0)
		{
			$this->pog_query = "update `assignmentgrade` set 
			`assignment_id`='".$this->escape($this->assignment_id)."', 
			`student_id`='".$this->escape($this->student_id)."', 
			`points`='".$this->escape($this->points)."', 
			`grade_id`='".$this->escape($this->grade_id)."', 
			`comment`='".$this->escape($this->comment)."', 
			`is_waived`='".$this->escape($this->is_waived)."', 
			`due`='".$this->due."', 
			`assigned`='".$this->assigned."' where `assignmentgradeid`='".$this->assignmentgradeId."'";
		}
		else
		{
			$this->pog_query = "insert into `assignmentgrade` (`assignment_id`, `student_id`, `points`, `grade_id`, `comment`, `is_waived`, `due`, `assigned` ) values (
			'".$this->escape($this->assignment_id)."', 
			'".$this->escape($this->student_id)."', 
			'".$this->escape($this->points)."', 
			'".$this->escape($this->grade_id)."', 
			'".$this->escape($this->comment)."', 
			'".$this->escape($this->is_waived)."', 
			'".$this->due."', 
			'".$this->assigned."' )";
		}
		$insertId = Database::InsertOrUpdate($this->pog_query, $connection);
		if ($this->assignmentgradeId == "")
		{
			$this->assignmentgradeId = $insertId;
		}
		return $this->assignmentgradeId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $assignmentgradeId
	*/
	function SaveNew()
	{
		$this->assignmentgradeId = '';
		return $this->save();
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete()
	{
		$connection = Database::Connect();
		$this->pog_query = "delete from `assignmentgrade` where `assignmentgradeid`='".$this->assignmentgradeId."'";
		return Database::NonQuery($this->pog_query, $connection);
	}
	
	
	/**
	* Deletes a list of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param bool $deep 
	* @return 
	*/
	function deleteList($fcv_array)
	{
		if (sizeof($fcv_array) > 0)
		{
			$connection = Database::Connect();
			$pog_query = "delete from `assignmentgrade` where ";
			for ($i=0, $c=sizeof($fcv_array); $i<$c; $i++)
			{
				if (sizeof($fcv_array[$i]) == 1)
				{
					$pog_query .= " ".$fcv_array[$i][0]." ";
					continue;
				}
				else
				{
					if ($i > 0 && sizeof($fcv_array[$i-1]) !== 1)
					{
						$pog_query .= " AND ";
					}
					if (isset($this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes']) && $this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'NUMERIC' && $this->pog_attribute_type[$fcv_array[$i][0]]['db_attributes'][0] != 'SET')
					{
						$pog_query .= "`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." '".$this->escape($fcv_array[$i][2])."'";
					}
					else
					{
						$pog_query .= "`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." '".$fcv_array[$i][2]."'";
					}
				}
			}
			return Database::NonQuery($pog_query, $connection);
		}
	}
}
?>