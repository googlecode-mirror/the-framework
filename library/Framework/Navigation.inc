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
    private $_navigation_root;
    private $_allowed_navigation_root;

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
        $xml = simplexml_load_file($this->_file_dir);

        $root = new Framework_Navigation_Item(
            array(
                'controller' => 'root',
                'action'     => 'root',
                'label'      => 'root',
                'auth'       => '*',
                'nav_path'   => ''
            )
        );
        $acl = Framework_Registry::get('acl');

        foreach ($xml as $item) {
            $this->_processXmlItem($item, $root, $acl);
        }

        $this->_navigation_root = $root;
    }

    private function _processXmlItem($xml, $parent, $acl)
    {
        if ($xml->getName() === 'item') {
            
            $a_auth = explode(':', $xml->auth);
            $is_auth = true;
            if ($a_auth[0] !== '*') {
                $is_auth = $acl->isAuthorized(
                    Framework_Registry::get('role'),
                    $a_auth[0],
                    isset($a_auth[1]) ? $a_auth[1] : ''
                );
            }
            
            if ($is_auth === true) {
                $item = new Framework_Navigation_Item(
                    array(
                        'id'         => (string) $xml->id,
                        'label'      => (string) utf8_encode($xml->label),
                        'auth'       => explode(':', $xml->auth),
                        'controller' => (string) $xml->controller,
                        'action'     => (string) $xml->action,
                        'nav_path'   => explode(':', $xml->nav_path)
                    )
                );
                $parent->addChild($item);
                $children = $xml->children();
                foreach ($children as $child) {
                    $this->_processXmlItem($child, $item, $acl);
                }
            }
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
            $this->_init();
            $_SESSION['navigation_root'] = serialize($this->_navigation_root);
            $_SESSION['navigation_role'] = Framework_Registry::get('role');
            write_info_msg("Navigation", "Returning allowed items.");
        } else {
            $this->_navigation_root = unserialize($_SESSION['navigation_root']);
            write_info_msg("Navigation", "Returning allowed items from session.");
        }

        return $this->_navigation_root;
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
