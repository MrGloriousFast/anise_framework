#ifndef NODECONFIG_H
#define NODECONFIG_H

#include <QMap>
#include <QVariant>

class QObject;

class CNodeConfig
{
  public:
    // The structure that defined the details of a parameter.
    struct SParameterTemplate {
        QString name;
        QVariant::Type type; // Type expected for the value.
        QVariant value;      // The value this parameter will hold.
        QString description;
        SParameterTemplate()
            : name()
            , type(QVariant::Invalid)
            , value()
            , description() {}
    };
    struct SGateTemplate {
        QString name;
        QString msg_type;
        SGateTemplate(QString p_name, QString p_msg_type)
            : name(p_name)
            , msg_type(p_msg_type) {}
    };

  private:
    // The name assigned by the user to this node.
    QString m_name;
    // The collection of configuration parameters of the Node.
    // ... They're mutable to allow the user of the Node clases to modify
    // ... the value type of the parameters while disallowing the addition
    // ... or deletion of parameters to the configuration template.
    mutable QMap<QString, SParameterTemplate> m_parameter_template_map;
    mutable QList<SGateTemplate> m_input_templates;
    mutable QList<SGateTemplate> m_output_templates;

  public:
    explicit CNodeConfig();

    void setName(QString name);
    const QString getName() const;
    // Set the value of parameter specified in the template.
    bool setParameter(QString key, QVariant value) const;

    // Facilities for adding different parameters to the configuration
    // ... template.
    void addFilename(QString key, QString name, QString description);
    void addBool(QString key, QString name, QString description);

    // Facilities for adding inputs and outputs.
    void addInput(QString name, QString msg_type);
    void addOutput(QString name, QString msg_type);

    // Getters und Setters.
    const SParameterTemplate *getParameter(QString key) const;
    const QList<SGateTemplate> &getInputTemplates() const;
    const QList<SGateTemplate> &getOutputTemplates() const;
};

#endif // NODECONFIG_H
