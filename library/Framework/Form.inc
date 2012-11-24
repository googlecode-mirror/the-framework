<?php
/**
 * Form.inc
 *
 * This file contains the Framework_Form class.
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
 * This class is the base for every Form class in the application.
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  Release: 1
 * @abstract
 */
abstract class Framework_Form
{
    protected $a_err_messages = array();
    protected $a_fields       = array();

    /**
     * Constructor for the Framework_Form class
     *
     * @param array $a_inputs the input array
     *
     * @access public
     * @return Framework_Form
     */
    public function __construct($a_inputs = array())
    {
        $this->a_fields = filter_var_array($a_inputs, $this->getSanitizeArray());
    }

    /**
     * returns an associative array containing the sanitization data for the
     * form fields.(eg. 'field_name' => FILTER_SANITIZE_EXAMPLE)
     *
     * @access protected
     * @return array
     */
    protected abstract function getSanitizeArray();

    /**
     * returns an associative array containing the validation data for the form
     * fields.(eg. 'field_name' => FILTER_VALIDATE_EXAMPLE)
     *
     * @access protected
     * @return array
     */
    protected abstract function getValidateArray();

    /**
     * returns an array containing the mandatory field names.
     *
     * @access protected
     * @return array
     */
    protected abstract function getMandatoryArray();

    /**
     * Validates the Form
     *
     * @return bool
     */
    public function validate()
    {
        $a_validated_input = filter_var_array($this->a_fields, $this->getValidateArray());

        foreach ($a_validated_input as $k => $v) {
            if ($v === false) {
                $this->a_err_messages[$k] = gettext('O valor inserido não é válido');
            }
        }

        foreach ($this->getMandatoryArray() as $k) {
            if (filter_validate_not_empty($this->a_fields[$k]) === false) {
                $this->a_err_messages[$k] = gettext('Este campo é obrigatório.');
            }
        }

        return sizeof($this->a_err_messages) === 0;
    }


    public function hasErrors()
    {
        return sizeof($this->a_err_messages) > 0;
    }

    /**
     * Returns an error message if it exists.
     *
     * @param string $key the position in the array
     *
     * @access public
     * @return string
     */
    public function getErrorMessage($key)
    {
        if (isset($this->a_err_messages[$key])) {
            return $this->a_err_messages[$key];
        }
    }

    /**
     * Adds an error message to the err messages array.
     *
     * @param string $fieldName the key in the array
     * @param string $message   the error message
     *
     * @access public
     * @return void
     */
    public function addErrorMessage($fieldName, $message)
    {
        $this->a_err_messages[$fieldName] = $message;
    }

    /**
     * Returns a value
     *
     * @param string $k the key of the value
     *
     * @access public
     * @return mixed
     */
    public function getValue($k)
    {
        if (isset($this->a_fields[$k])) {
            return $this->a_fields[$k];
        }
    }

    /**
     * Returns all the values in the form.
     *
     * @return array
     */
    public function getValues()
    {
        return $this->a_fields;
    }

    /**
     * Sets a value in a form.
     *
     * @param string $key   the key in the array to store the field value.
     * @param mixed  $value the value of the field
     *
     * @return void
     */
    public function setValue($key, $value)
    {
        $this->a_fields[$key] = $value;
    }

    /**
     * Returns a json formated version of the fields.
     *
     * @return string
     */
    public function __toString()
    {
        $output = get_called_class() . ' : { ' .
            'a_fields : ' . json_encode($this->a_fields) . ',' .
            'a_err_messages : ' . json_encode($this->a_err_messages) . ',' .
            'a_mandatory : ' . json_encode($this->getMandatoryArray()) . ',' .
            'a_sanitize : ' . json_encode($this->getSanitizeArray()) . ',' .
            'a_validate : ' . json_encode($this->getValidateArray()) .
            ' }';
        return $output;
    }
}