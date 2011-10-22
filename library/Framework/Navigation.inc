<?php
/**
 * Navigation.inc
 *
 * This file contains the Framework_Navigation class.
 *
 * PHP versions 4 and 5
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  SVN: 1
 */
/**
 * This class will read the navigation.xml file and parse it into an appropriate
 * structure.
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  Release: 1
 */
class Framework_Navigation
{
    /**
     * The directory of the navigation file.
     *
     * @access private
     * @var string
     */
    private $_file_dir;
    private $_items;
    private $_cur_controller;
    private $_cur_action;

    /**
     * The constructor for the Framework_Navigation class
     *
     * @param string $file_dir the directory for the xml file
     */
    public function __construct($file_dir = null)
    {
        $file_dir = !isset($file_dir) ?
        BASE_PATH . '/application/Config/navigation.xml'
        : $file_dir;
        $this->_file_dir = $file_dir;
        $this->_items = array();
    }

    /**
     * Initializes the navigation.
     *
     * @return void
     */
    private function _init()
    {
        $item = array();
        $a_ser_items = array();
        $xml = simplexml_load_file($this->_file_dir);
        foreach ($xml as $nav_item) {
            $item['label'] = (string) $nav_item->label;
            $item['auth'] = explode(':', $nav_item->auth);
            $item['controller'] = (string) $nav_item->controller;
            $item['action'] = (string) $nav_item->action;
            $item['nav_path'] = explode(':', $nav_item->nav_path);
            $this->_items[] = new Framework_Navigation_Item($item);
        }
    }

    /**
     * Returns the allowed items for a user
     *
     * @return array
     */
    public function getAllowedItems()
    {
        if (!isset($_SESSION['navigation_role'])
        || (isset($_SESSION['navigation_role'])
        && $_SESSION['navigation_role'] !== Framework_Registry::get('role'))
        ) {
            $new_role = true;
        } else {
            $new_role = false;
        }

        if (false === isset($_SESSION['navigation_allowed'])
        || true === $new_role
        ) {
            $this->_init();
            $return_arr = array();
            $a_auth = null;
            $is_auth = false;
            $acl = Framework_Registry::get('acl');

            foreach ($this->_items as $item) {
                $a_auth = $item->getAuth();
                $is_auth = $acl->isAuthorized(
                Framework_Registry::get('role'),
                    $a_auth[0],
                    isset($a_auth[1]) ? $a_auth[1] : ''
                );

                if (true === $is_auth) {
                    $return_arr[] = $item;
                }
            }

            $_SESSION['navigation_allowed'] = serialize($return_arr);
            $_SESSION['navigation_role'] = Framework_Registry::get('role');
            write_info_msg("Navigation", "Returning allowed items.");
        } else {
            $return_arr = unserialize($_SESSION['navigation_allowed']);
            write_info_msg("Navigation", "Returning allowed items from session.");
        }

        return $return_arr;
    }

    /**
     * Sets the current controller
     *
     * @param string $controller the name of the controller
     *
     * @return void
     */
    public function setCurrentController($controller)
    {
        $this->_cur_controller = $controller;
    }

    /**
     * Returns the current controller name
     *
     * @return string
     */
    public function getCurrentController()
    {
        return $this->_cur_controller;
    }

    /**
     * Sets the current action
     *
     * @param string $action the name of the action
     *
     * @return void
     */
    public function setCurrentAction($action)
    {
        $this->_cur_action = $action;
    }

    /**
     * Returns the current action name
     *
     * @return string
     */
    public function getCurrentAction()
    {
        return $this->_cur_action;
    }
}