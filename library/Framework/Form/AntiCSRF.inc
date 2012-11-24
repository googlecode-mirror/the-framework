<?php
/**
 * AntiCSRF.inc
 *
 * This file contains the Framework_Form_AntiCSRF class.
 *
 * PHP versions 4 and 5
 *
 * @category   Framework
 * @package    Framework
 * @subpackage Form
 * @author     Tiago Seixas <tiagoafseixas@gmail.com>
 * @license    GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version    SVN: 1
 */
/**
 * This class extends the Framework_Form class and implements some
 * methods that prevent CSRF.
 *
 * @tutorial http://codeutopia.net/blog/2008/10/16/how-to-csrf-protect-all-your-forms/
 *
 * @category   Framework
 * @package    Framework
 * @subpackage Form
 * @author     Tiago Seixas <tiagoafseixas@gmail.com>
 * @license    GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version    Release: 1
 * @abstract
 */
abstract class Framework_Form_AntiCSRF extends Framework_Form
{
    private $_spinner;

    /**
     * Constructs the AntiSpam fields in the form.
     *
     * @param array $params the parameters
     */
    public function __construct($params = array())
    {
        if (isset($params['spinner'])
        ) {
            $this->_spinner = $params['spinner'];
        } else {
            $this->_spinner = sha1(
                $_SERVER['REMOTE_ADDR'] . session_id() . 'spinner'
            );
            $_SESSION['anti_csrf'] = array(
                'spinner' => $this->_spinner
            );
        }
        parent::__construct($params);
    }

    /**
     * Regenerates the elements of the AntiSpam verification.
     *
     * @return void
     */
    public function regenerateAntiCSRF()
    {
        $this->_spinner = sha1(
            $_SERVER['REMOTE_ADDR'] . session_id() . 'spinner' . time()
        );

        if (isset($_SESSION['anti_csrf'])) {
            unset($_SESSION['anti_csrf']);
        }
        $_SESSION['anti_csrf'] = array(
            'spinner' => $this->_spinner
        );
    }

    /**
     * Validates the antispam fields.
     * 
     * @todo: Validate the timestamp against some time (i.e. 30min)
     *  
     * @return bool
     */
    public function validateAntiCSRF()
    {
        $old_spinner = $_SESSION['anti_csrf']['spinner'];
        if ($this->_spinner === null
            || $old_spinner !== $this->_spinner
        ) {
            write_error_msg(
                get_called_class(),
            	'Received Spinner is not the same as the server\'s'
            );
            $return_val = false;
        }
        return true;
    }

    /**
     * Validates the form.
     *
     * @see Framework_Form::validate()
     *
     * @return boolean
     */
    public function validate()
    {
        return $this->validateAntiCSRF() && parent::validate();
    }
    /**
     * Returns the spinner value.
     *
     * @return string
     */
    public function getSpinner()
    {
        return $this->_spinner;
    }
}