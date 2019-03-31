import six
from google.cloud import language
from google.cloud.language import enums
from google.cloud.language import types
import os


def checkEntities(keyPath, text):
    # Creates environment variable
    os.environ['GOOGLE_APPLICATION_CREDENTIALS'] = keyPath

    client = language.LanguageServiceClient()

    if isinstance(text, six.binary_type):
        text = text.decode('utf-8')

    # Instantiates a plain text document.
    document = types.Document(
        content=text,
        type=enums.Document.Type.PLAIN_TEXT)

    # API call
    entities = client.analyze_entities(document).entities

    # Test output
    for entity in entities:
        entity_type = enums.Entity.Type(entity.type)
        print('=' * 20)
        print(u'{:<16}: {}'.format('name', entity.name))
        print(u'{:<16}: {}'.format('type', entity_type.name))
        print(u'{:<16}: {}'.format('salience', entity.salience))
        print(u'{:<16}: {}'.format('wikipedia_url',
            entity.metadata.get('wikipedia_url', '-')))
        print(u'{:<16}: {}'.format('mid', entity.metadata.get('mid', '-')))

    results = []
    for entity in entities:
        results.append(entity.name)

    return results


if __name__ == "__main__":
    keyPath = "/Users/lihanzhu/Desktop/lahacks/Cloud/service-account.json"
    text = "The fridge is on a key."

    print(checkEntities(keyPath, text))