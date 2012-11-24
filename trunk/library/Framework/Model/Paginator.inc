<?php
/**
 * Paginator.inc
 *
 * This file contains the Framework_Model_Paginator class.
 *
 * PHP versions 4 and 5
 * 
 * @category   Framework
 * @package    Framework
 * @subpackage Model
 * @author     Tiago Seixas <tiagoafseixas@gmail.com>
 * @license    GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version    SVN: 1
 */
/**
 * This class extends the Framework_Model class and implements some
 * methods that facilitate the pagination of the results
 *
 * @category   Framework
 * @package    Framework
 * @subpackage Model
 * @author     Tiago Seixas <tiagoafseixas@gmail.com>
 * @license    GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version    Release: 1
 * @abstract
 */
abstract class Framework_Model_Paginator extends Framework_Model
{
    protected $controller;
    protected $action;

    protected $items_per_page = 10;
    protected $total_items = 0;
    protected $total_pages;
    protected $current_page = 1;
    protected $params = array();
    protected $data_set = array();

    private static $_ORDER_BY_STMT = <<<OBS
        ORDER BY %s %s
OBS;
    /**
     * Executes the pagination.
     * 
     * @return void
     */
    abstract public function paginate();

    /**
     * Returns the number of items per page.
     * 
     * @return int
     */
    public function getItemsPerPage()
    {
        return $this->items_per_page;
    }

    public function setItemsPerPage($items_per_page)
    {
        $this->items_per_page = $items_per_page;
    }

    /**
     * Return the current page
     * 
     * @return int
     */
    public function getCurrentPage()
    {
        return $this->current_page;
    }

    /**
     * Returns the total number of items.
     * 
     * @access public
     * @return int
     */
    public function getTotalItems()
    {
        return $this->total_items;
    }

    public function setTotalItems($total_items)
    {
        $this->total_items = $total_items;
    }

    /**
     * Returns the entire current data set.
     * 
     * @access public
     * @return array
     */
    public function getDataSet()
    {
        return $this->data_set;
    }

    public function setDataSet($ds)
    {
        $this->data_set = $ds;
    }

    /**
     * sets the controller name that is used by the paginator.
     * 
     * @param string $c the controller name
     * 
     * @access public
     * @return void
     */
    public function setController($c)
    {
        $this->controller = $c;
    }

    /**
     * Returns the controller
     * 
     * @return string
     */
    public function getController()
    {
        return $this->controller;
    }

    /**
     * sets the action name that is used by the paginator.
     * 
     * @param string $a the action name
     * 
     * @access public
     * @return void
     */
    public function setAction($a)
    {
        $this->action = $a;
    }

    /**
     * Returns the action
     * 
     * @return string
     */
    public function getAction()
    {
        return $this->action;
    }

    /**
     * Returns the link for the next page.
     * 
     * @uses $this->getPageLink
     * 
     * @access public
     * @return int
     */
    public function getNextPageLink()
    {
        if ($this->current_page < $this->getTotalPages()) {
            return $this->getPageLink($this->current_page + 1);
        }
    }

    /**
     * Calculates the total number of pages.
     * 
     * @return int
     */
    public function getTotalPages()
    {
        if (isset($this->total_pages) === false) {
            if ($this->total_items > $this->items_per_page) {
                $total_pages = intval(($this->total_items/$this->items_per_page));
                if ($this->total_items%$this->items_per_page !== 0) {
                    $total_pages += 1;
                }
                $this->total_pages = $total_pages;
           } else if ($this->total_items > 0){
                $this->total_pages = 1;
            } else {
                $this->total_pages = 0;
            }
        }
        return $this->total_pages;
    }

    /**
     * Returns the parameters used to filter the results.
     * 
     * @return array
     */
    public function getWhereParams()
    {
        return $this->params;
    }

    public function fetchTotalItems($finder_query, $params)
    {
        try {
            if (false === self::$dbh instanceof PDO) {
                $this->connect();
            }
            $stmt = self::$dbh->prepare($this->getCountStatement($finder_query));
            $stmt->execute($params);
            $res = $stmt->fetch();
            $this->total_items = $res[0];
        } catch (PDOException $e) {
            write_error_msg('Framework_Model_Paginator', $e);
        }
    }

    public function fetchDataSet($finder_query, $params)
    {
        try {
            $offset = ($this->current_page-1) * $this->items_per_page;
            $stmt = self::$dbh->prepare(
                $this->getPaginationStatement($finder_query)
            );

            $stmt->execute($params);
            $this->data_set = $stmt->fetchAll(PDO::FETCH_ASSOC);
        } catch (PDOException $e) {
            write_error_msg("Classified Paginator", $e);
        }
    }

    /**
     * Returns a count query for the query received as a parameter
     *
     * @param mixed $finder_query the base query for the statement
     *
     * @access public
     *
     * @return string
     */
    public function getCountStatement($finder_query)
    {
        return "SELECT COUNT(1) FROM ($finder_query) X";
    }

    /**
     * Returns a pagination query for the query received as a parameter
     *
     * @param mixed $finder_query the base query for the statement
     *
     * @access public
     *
     * @return string
     */
    public function getPaginationStatement($finder_query)
    {
        return sprintf(
            "$finder_query LIMIT %d OFFSET %d",
            $this->items_per_page,
            ($this->current_page-1) * $this->items_per_page
        );
    }

    /**
     * Returns an order by clause
     * 
     * @param  string $column_name the name of the column to order
     * @param  string $order the order value
     * @access protected
     * @return string
     */
    protected function getOrderByClause($column_name, $order = "DESC")
    {
        return sprintf(self::$_ORDER_BY_STMT, $column_name, $order);
    }
}
