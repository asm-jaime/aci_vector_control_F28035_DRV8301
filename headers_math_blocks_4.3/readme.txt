Change History

1. PID_REG3.H --> PID_REG Macro renamed to PID_REG3 macro
              --> PID_REG3_POS macro created to work with angle inputs

2. RESOLVER.H --> variables redefined to _iq format, making it compatible for both fixed and floating point cpus
              --> RESOLVER_MACRO_F is created to provide a floating point version of the original macro RESOLVER_MACRO