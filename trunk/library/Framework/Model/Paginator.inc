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
 * @subpackage ACL
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
 * @subpackage ACL
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
    protected $where_params = array();
    protected $data_set = array();

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
            } else {
                $this->total_pages = 1;
            }
        }
        return $this->total_pages;
    }

    public function getWhereParams()
    {
        return $this->where_params;
    }
}