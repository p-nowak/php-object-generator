<?php
/*
	This SQL query will create the table to store your object.

	CREATE TABLE `assignment_grade` (
	`assignment_gradeid` int(11) NOT NULL auto_increment,
	`assignment_id` INT NOT NULL,
	`student_id` INT NOT NULL,
	`points` INT NOT NULL,
	`grade_id` INT NOT NULL,
	`comment` VARCHAR(255) NOT NULL,
	`is_waived` TINYINT NOT NULL,
	`due` DATE NOT NULL,
	`assigned` DATE NOT NULL, PRIMARY KEY  (`assignment_gradeid`)) ENGINE=MyISAM;
*/

/**
* <b>AssignmentGrade</b> class with integrated CRUD methods.
* @author Php Object Generator
* @version POG 3.2 / PHP5
* @copyright Free for personal & commercial use. (Offered under the BSD license)
* @link http://www.phpobjectgenerator.com/?language=php5&wrapper=pog&objectName=AssignmentGrade&attributeList=array+%28%0A++0+%3D%3E+%27assignment_id%27%2C%0A++1+%3D%3E+%27student_id%27%2C%0A++2+%3D%3E+%27points%27%2C%0A++3+%3D%3E+%27grade_id%27%2C%0A++4+%3D%3E+%27comment%27%2C%0A++5+%3D%3E+%27is_waived%27%2C%0A++6+%3D%3E+%27due%27%2C%0A++7+%3D%3E+%27assigned%27%2C%0A%29&typeList=array+%28%0A++0+%3D%3E+%27INT%27%2C%0A++1+%3D%3E+%27INT%27%2C%0A++2+%3D%3E+%27INT%27%2C%0A++3+%3D%3E+%27INT%27%2C%0A++4+%3D%3E+%27VARCHAR%28255%29%27%2C%0A++5+%3D%3E+%27TINYINT%27%2C%0A++6+%3D%3E+%27DATE%27%2C%0A++7+%3D%3E+%27DATE%27%2C%0A%29
*/
include_once('class.pog_base.php');
class AssignmentGrade extends POG_Base
{
	public $assignment_gradeId = '';

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
		"assignment_gradeId" => array('db_attributes' => array("NUMERIC", "INT")),
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
	* @param integer $assignment_gradeId 
	* @return object $AssignmentGrade
	*/
	function Get($assignment_gradeId)
	{
		$connection = Database::Connect();
		$this->pog_query = "select * from `assignment_grade` where `assignment_gradeid`='".intval($assignment_gradeId)."' LIMIT 1";
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$this->assignment_gradeId = $row['assignment_gradeid'];
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
	* Returns a sorted array of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param string $sortBy 
	* @param boolean $ascending 
	* @param int limit 
	* @return array $assignment_gradeList
	*/
	function GetList($fcv_array = array(), $sortBy='', $ascending=true, $limit='')
	{
		$connection = Database::Connect();
		$sqlLimit = ($limit != '' ? "LIMIT $limit" : '');
		$this->pog_query = "select * from `assignment_grade` ";
		$assignment_gradeList = Array();
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
							$value =  POG_Base::IsColumn($fcv_array[$i][2]) ? $fcv_array[$i][2] : "'".$this->Escape($fcv_array[$i][2])."'";
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
			$sortBy = "assignment_gradeid";
		}
		$this->pog_query .= " order by ".$sortBy." ".($ascending ? "asc" : "desc")." $sqlLimit";
		$thisObjectName = get_class($this);
		$cursor = Database::Reader($this->pog_query, $connection);
		while ($row = Database::Read($cursor))
		{
			$assignment_grade = new $thisObjectName();
			$assignment_grade->assignment_gradeId = $row['assignment_gradeid'];
			$assignment_grade->assignment_id = $this->Unescape($row['assignment_id']);
			$assignment_grade->student_id = $this->Unescape($row['student_id']);
			$assignment_grade->points = $this->Unescape($row['points']);
			$assignment_grade->grade_id = $this->Unescape($row['grade_id']);
			$assignment_grade->comment = $this->Unescape($row['comment']);
			$assignment_grade->is_waived = $this->Unescape($row['is_waived']);
			$assignment_grade->due = $row['due'];
			$assignment_grade->assigned = $row['assigned'];
			$assignment_gradeList[] = $assignment_grade;
		}
		return $assignment_gradeList;
	}
	
	
	/**
	* Saves the object to the database
	* @return integer $assignment_gradeId
	*/
	function Save()
	{
		$connection = Database::Connect();
		$rows = 0;
		if ($this->assignment_gradeId!=''){
			$this->pog_query = "select `assignment_gradeid` from `assignment_grade` where `assignment_gradeid`='".$this->assignment_gradeId."' LIMIT 1";
			$rows = Database::Query($this->pog_query, $connection);
		}
		if ($rows > 0)
		{
			$this->pog_query = "update `assignment_grade` set 
			`assignment_id`='".$this->Escape($this->assignment_id)."', 
			`student_id`='".$this->Escape($this->student_id)."', 
			`points`='".$this->Escape($this->points)."', 
			`grade_id`='".$this->Escape($this->grade_id)."', 
			`comment`='".$this->Escape($this->comment)."', 
			`is_waived`='".$this->Escape($this->is_waived)."', 
			`due`='".$this->due."', 
			`assigned`='".$this->assigned."' where `assignment_gradeid`='".$this->assignment_gradeId."'";
		}
		else
		{
			$this->pog_query = "insert into `assignment_grade` (`assignment_id`, `student_id`, `points`, `grade_id`, `comment`, `is_waived`, `due`, `assigned` ) values (
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
		if ($this->assignment_gradeId == "")
		{
			$this->assignment_gradeId = $insertId;
		}
		return $this->assignment_gradeId;
	}
	
	
	/**
	* Clones the object and saves it to the database
	* @return integer $assignment_gradeId
	*/
	function SaveNew()
	{
		$this->assignment_gradeId = '';
		return $this->Save();
	}
	
	
	/**
	* Deletes the object from the database
	* @return boolean
	*/
	function Delete()
	{
		$connection = Database::Connect();
		$this->pog_query = "delete from `assignment_grade` where `assignment_gradeid`='".$this->assignment_gradeId."'";
		return Database::NonQuery($this->pog_query, $connection);
	}
	
	
	/**
	* Deletes a list of objects that match given conditions
	* @param multidimensional array {("field", "comparator", "value"), ("field", "comparator", "value"), ...} 
	* @param bool $deep 
	* @return 
	*/
	function DeleteList($fcv_array)
	{
		if (sizeof($fcv_array) > 0)
		{
			$connection = Database::Connect();
			$pog_query = "delete from `assignment_grade` where ";
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
						$pog_query .= "`".$fcv_array[$i][0]."` ".$fcv_array[$i][1]." '".$this->Escape($fcv_array[$i][2])."'";
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